//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#ifndef WEB_SERVER_TYPES_H
#define WEB_SERVER_TYPES_H

#include <iostream>
#include <map>
#include <utils/string/string.h>

class Response {
public:
    Response() = default;

    void SetVersion(std::string obj);
    std::string GetVersion() const;

    void SetStatusCode(std::string obj);
    std::string GetStatusCode() const;

    void SetReasonPhrase(std::string obj);
    std::string GetReasonPhrase() const;

    void SetHeadAttr(std::string key, std::string val);
    std::string GetHeadAttr(std::string key) const;

    void SetBody(std::string obj);
    std::string GetBody() const;

    std::string GetStr() const;
private:
    std::string version_;
    std::string status_code_;
    std::string reason_phrase_;

    std::map<std::string, std::string> head_;

    std::string body_;
};

#endif //WEB_SERVER_TYPES_H
