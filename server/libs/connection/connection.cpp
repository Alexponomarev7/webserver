//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include <server/libs/daemon/daemontools.h>
#include <utils/sys/epoll_api.h>
#include "connection.h"

Connection::Connection(int port) : storage_(FileManager("/Users/lexolordan/webserver/cmake-build-debug/static")) {
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

    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = INADDR_ANY,
            .sin_port = htons(port)
    };

    if (bind(socket_, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        close(socket_);
        std::string status = (StringBuilder() << "[SERVER] Can't bind " << port << " port.").Get();
        Logger::Log(status, SERVER);
        throw std::runtime_error(status);
    }

    listen(socket_, 5);
    Logger::Log((StringBuilder() << "[SERVER] Binded on " << port << " port.").Get(), SERVER);
}

void Connection::Accept(std::vector<int> fds) {
  struct sockaddr_in cli_addr;
  int client_fd;
  socklen_t sin_len = sizeof(cli_addr);

  make_non_blocking(socket_);

  size_t current = 0;
  while (Daemon::DaemonTools::IsOpen()) {
    client_fd = accept(socket_,
                       (struct sockaddr *) &cli_addr,
                       &sin_len);
    if (client_fd == -1)
      continue;

    Logger::Log("[SERVER] Got connection.", SERVER);

    make_non_blocking(client_fd);
    write(fds[current], &client_fd, sizeof(client_fd));
    current = (current + 1) % fds.size();
  }

}

void Connection::Handle(int fd, Connection* connection) {
  int client_fd;
  while (Daemon::DaemonTools::IsOpen()) {
    read(fd, &client_fd, sizeof(client_fd));
    Query query = QueryHandler::RecieveFrom(client_fd);

    Response response;
    if (query.GetHost() != connection->host_) {
      Logger::Log("[SERVER] Proxy redirection.", SERVER);
      response = QueryHandler::GetProxy(query, connection->GetStorage());
    } else {
      response = QueryHandler::GetResponse(query, connection->GetStorage());
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