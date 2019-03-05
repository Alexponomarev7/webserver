//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#ifndef WEB_SERVER_STRING_H
#define WEB_SERVER_STRING_H

#include <string>

class StringBuilder {
public:
    StringBuilder() = default;

    StringBuilder& operator<<(int obj);
    StringBuilder& operator<<(std::string obj);

    std::string Get() const;

    ~StringBuilder() = default;
private:
    std::string buffer_;
};


#endif //WEB_SERVER_STRING_H
