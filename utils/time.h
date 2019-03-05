//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#ifndef WEB_SERVER_TIME_H
#define WEB_SERVER_TIME_H

#include <iostream>

class Time {
public:
    static std::string AdvancedFormat();
private:
    static time_t rawtime_;
    static struct tm* timeinfo_;
    static char buffer_[80];
};

#endif //WEB_SERVER_TIME_H
