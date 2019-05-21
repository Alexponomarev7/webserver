//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include <utils/logger/logger.h>
#include <utils/time.h>

std::mutex Logger::mutex_ = std::mutex();

size_t Logger::logging_parse_ = SERVER | DAEMON | MONITOR;

void Logger::Log(std::string message, LogType type) {
    if (!(type & logging_parse_))
      return;

    mutex_.lock();
    FILE* f;

    f = fopen("/root/webserver/log.txt", "a+");

    fprintf(f, "%s: %s\n", Time::AdvancedFormat().c_str(), message.c_str());

    fclose(f);

    mutex_.unlock();
}

void Logger::SetLoggingLevel(size_t level) {
  logging_parse_ = level;
}