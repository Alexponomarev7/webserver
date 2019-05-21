//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#ifndef WEB_SERVER_LOGGER_H
#define WEB_SERVER_LOGGER_H

#include <iostream>
#include <fcntl.h>
#include <ctime>
#include <mutex>

enum LogType {
  DEFAULT = 0,
  SERVER = 1,
  DAEMON = 2,
  MONITOR = 4
};

class Logger {
public:
    Logger() = default;

    static void Log(std::string s, LogType type = DEFAULT);

    static void SetLoggingLevel(size_t level);

    ~Logger() = default;
private:
    static std::mutex mutex_;
    static size_t logging_parse_;
};


#endif //WEB_SERVER_LOGGER_H
