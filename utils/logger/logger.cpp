//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include <utils/logger/logger.h>
#include <utils/time.h>

void Logger::Log(std::string message) const {
    freopen("log.txt", "a+", stdout);
    std::cout << Time::AdvancedFormat() << ": " << message << std::endl;
}