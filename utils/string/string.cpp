//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include "string.h"

StringBuilder& StringBuilder::operator<<(int obj) {
    buffer_ += std::to_string(obj);
    return *this;
}

StringBuilder& StringBuilder::operator<<(std::string obj) {
    buffer_ += obj;
    return *this;
}

std::string StringBuilder::Get() const {
    return buffer_;
}