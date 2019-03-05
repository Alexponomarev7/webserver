//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#ifndef WEB_SERVER_LOGGER_H
#define WEB_SERVER_LOGGER_H

#include <iostream>
#include <fcntl.h>
#include <ctime>

class Logger {
public:
    Logger() = default;

    void Log(std::string s) const;

    ~Logger() = default;
};


#endif //WEB_SERVER_LOGGER_H
