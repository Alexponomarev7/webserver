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

#include <utils/logger/logger.h>
#include <utils/string/string.h>
#include <server/libs/connection/types.h>
#include <server/libs/connection/testlib.h>

class Connection {
public:
    Connection();

    void BindPort(int port);
    void Handle();

    ~Connection();
private:
    int socket_;
    Logger logger_;
};



#endif //WEB_SERVER_CONNECTION_H
