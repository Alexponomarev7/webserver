//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include "connection.h"

Connection::Connection() {
    logger_ = Logger();
    socket_ = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_ < 0) {
        std::string status = "Can't open socket.";
        logger_.Log(status);
        throw status;
    }

    int one = 1;
    setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

    logger_.Log("Create connection.");
    logger_.Log("Ready to attempt queries.");

}

void Connection::BindPort(int port) {
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    if (bind(socket_, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        close(socket_);
        std::string status = (StringBuilder() << "Can't bind " << port << " port.").Get();
        logger_.Log(status);
        throw status;
    }

    listen(socket_, 5);
    logger_.Log((StringBuilder() << "Binded on " << port << " port.").Get());
}

void Connection::Handle() {
    struct sockaddr_in cli_addr;
    int client_fd;
    socklen_t sin_len = sizeof(cli_addr);

    while (true) {
        client_fd = accept(socket_,
                           (struct sockaddr *) &cli_addr,
                           &sin_len);
        logger_.Log("Got connection");

        if (client_fd == -1) {
            logger_.Log("Can't accept");
            continue;
        }

        std::string response_string = SimpleResponse().GetStr();
        logger_.Log(response_string);
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
}