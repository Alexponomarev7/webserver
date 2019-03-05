//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include "time.h"

std::string Time::AdvancedFormat() {
    time(&rawtime_);
    timeinfo_ = localtime(&rawtime_);
    strftime(buffer_, sizeof(buffer_), "%d-%m-%Y %H:%M:%S", timeinfo_);
    return static_cast<std::string>(buffer_);
}

time_t Time::rawtime_;
tm* Time::timeinfo_;
char Time::buffer_[80];
