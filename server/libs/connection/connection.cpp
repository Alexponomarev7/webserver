//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include <server/libs/daemon/daemontools.h>
#include "connection.h"

Connection::Connection(int port) : storage_(FileManager("/root/webserver/static")) {
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    host_ = "127.0.0.1:" + std::to_string(port);

    if (socket_ < 0) {
        std::string status = "[SERVER] Can't open socket.";
        Logger::Log(status, SERVER);
        throw std::runtime_error(status);
    }

    int one = 1;
    setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

    Logger::Log("[SERVER] Create connection.", SERVER);
    Logger::Log("[SERVER] Ready to attempt queries.", SERVER);

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    if (bind(socket_, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        close(socket_);
        std::string status = (StringBuilder() << "[SERVER] Can't bind " << port << " port.").Get();
        Logger::Log(status, SERVER);
        throw std::runtime_error(status);
    }

    listen(socket_, 5);
    Logger::Log((StringBuilder() << "[SERVER] Binded on " << port << " port.").Get(), SERVER);
}

void Connection::Handle() {
    struct sockaddr_in cli_addr;
    int client_fd;
    socklen_t sin_len = sizeof(cli_addr);

    fcntl(socket_, F_SETFL, fcntl(socket_, F_GETFL) | O_NONBLOCK);

    while (Daemon::DaemonTools::IsOpen()) {
      client_fd = accept(socket_,
                         (struct sockaddr *) &cli_addr,
                         &sin_len);
      if (client_fd == -1)
        continue;

      Logger::Log("[SERVER] Got connection.", SERVER);

      Query query = QueryHandler::RecieveFrom(client_fd);

      Response response;
      if (query.GetHost() != host_) {
        Logger::Log("[SERVER] Proxy redirection.", SERVER);
        response = QueryHandler::GetProxy(query, GetStorage());
      } else {
        response = QueryHandler::GetResponse(query, GetStorage());
      }

      Logger::Log("[SERVER] " + response.GetStr(), SERVER);
      QueryHandler::SendTo(client_fd, response);

      close(client_fd);
    }
}

Connection::~Connection() {
  close(socket_);
  Logger::Log("[SERVER] Socket closed.", SERVER);
}