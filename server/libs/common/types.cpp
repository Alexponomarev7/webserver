//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include "types.h"

// implements Response
Response::Response(const std::string &data) {
  is_package_ = false;

  SetVersion("HTTP/1.1");
  SetStatusCode("200");
  SetReasonPhrase("OK");

  SetHeadAttr("Content-Type", "text/html; charset=UTF-8");

  SetBody(data);
}

void Response::SetVersion(std::string obj) {
    version_ = obj;
}

std::string Response::GetVersion() const {
    return version_;
}

void Response::SetStatusCode(std::string obj) {
    status_code_ = obj;
}

std::string Response::GetStatusCode() const {
    return status_code_;
}

void Response::SetReasonPhrase(std::string obj) {
    reason_phrase_ = obj;
}

std::string Response::GetReasonPhrase() const {
    return reason_phrase_;
}

void Response::SetHeadAttr(std::string key, std::string val) {
    head_[key] = val;
}

std::string Response::GetHeadAttr(std::string key) const {
    if (head_.find(key) != head_.end())
        return head_.at(key);
    return "";
}

void Response::SetBody(std::string obj) {
    body_ = obj;
}

std::string Response::GetBody() const {
    return body_;
}

std::string Response::GetStr() const {
    if (is_package_)
      return package_;

    StringBuilder builder = StringBuilder();

    builder << GetVersion() << " " << GetStatusCode() << " " << GetReasonPhrase() << "\n";
    for (auto item : head_) {
        builder << item.first << ": " << item.second << "\n";
    }
    builder << "\n";
    builder << GetBody();
    return builder.Get();
}

void Response::SetPackage(std::string package) {
  is_package_ = true;
  package_ = package;
}