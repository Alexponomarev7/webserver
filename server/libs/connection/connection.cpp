//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include <server/libs/daemon/daemontools.h>
#include "connection.h"

Connection::Connection(int port) {
    socket_ = socket(AF_INET, SOCK_STREAM, 0);

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

      Query query(client_fd);

      std::string response_string = SimpleResponse().GetStr();
      const char * response = response_string.c_str();
      ssize_t total_cnt = 0, now_cnt;
      while (total_cnt != strlen(response)) {
          now_cnt = write(client_fd, response + total_cnt, strlen(response) - total_cnt);
          total_cnt += now_cnt;
      }
      close(client_fd);
    }
}

Connection::~Connection() {
  close(socket_);
  Logger::Log("[SERVER] Socket closed.", SERVER);
}

Query::Query(int fd) {
  char buffer[4096];
  while (read(fd, buffer, sizeof(buffer)) == -1);
  Logger::Log(buffer, SERVER);
}