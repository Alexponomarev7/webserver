//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include "logger.h"

void Logger::Log(std::string message) const {
    freopen("log.txt", "a+", stdout);

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string time(buffer);

    std::cout << time << ": " << message << std::endl;
}