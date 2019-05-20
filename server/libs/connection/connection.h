//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#ifndef WEB_SERVER_CONNECTION_H
#define WEB_SERVER_CONNECTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <string>
#include <unordered_map>

#include <utils/logger/logger.h>
#include <utils/string/string.h>
#include <server/libs/common/types.h>
#include <server/libs/connection/testlib.h>

class Query {
 public:
  Query(int fd);
 private:
  std::unordered_map<std::string, std::string> data_;
};

class Connection {
 public:
  Connection() = default;

  Connection(int port);

  void Handle();

  ~Connection();
 private:
  int socket_;
};



#endif //WEB_SERVER_CONNECTION_H
