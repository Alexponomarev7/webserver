//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#ifndef WEB_SERVER_CONNECTION_H
#define WEB_SERVER_CONNECTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <string>
#include <unordered_map>

#include <utils/logger/logger.h>
#include <utils/string/string.h>
#include <server/libs/common/types.h>
#include <server/libs/connection/testlib.h>
#include <utils/sys/file_manager.h>
#include <utils/sys/helpers.h>

class Query {
 public:
  Query() = default;

  explicit Query(std::string s, std::vector<char> data = {}) {
    char buffer1[1024], buffer2[1024];

    sscanf(s.c_str(), "%s %s", buffer1, buffer2);

    data_["package"] = s;

    data_["method"] = buffer1;
    data_["path"] =  buffer2;

    data_["host"] = GetDataField(s, "Host: ");

    data_["Content-Type"] = GetDataField(s, "Content-Type: ");
    data_["accept"] = GetDataField(s, "Accept: ");
    data_["referer"] = GetDataField(s, "Referer: ");
    data_["Accept-Encoding"] = GetDataField(s, "Accept-Encoding: ");
    data_["Accept-Language"] = GetDataField(s, "Accept-Language: ");
    data_["Cookie"] = GetDataField(s, "Cookie: ");
    data_["Content-Length"] = GetDataField(s, "Content-Length: ");
    data_["Origin"] = GetDataField(s, "Origin: ");

    data_to_send_ = data;
  }

  void SetMethod(const std::string& method) {
    data_["method"] = method;
  }

  std::string GetMethod() const {
    return data_.at("method");
  }

  void SetPath(const std::string& path) {
    data_["path"] = path;
  }

  std::string GetPath() const {
    return data_.at("path");
  }

  void SetHost(const std::string& host) {
    data_["host"] = host;
  }

  std::string GetHost() const {
    return data_.at("host");
  }

  void SetPackage(const std::string& package) {
    data_["package"] = package;
  }

  std::string GetPackage() const {
    return data_.at("package");
  }

  std::vector<char> GetBasicPackage() const {
    std::string result = data_.at("method") + " " + data_.at("path") +
        " HTTP/1.1\r\nHost: " + data_.at("host") + "\r\nConnection: close\r\n";

    if (data_.at("accept") != "") {
      result = result + "Accept: " + data_.at("accept") + "\r\n";
    }

    if (data_.at("referer") != "") {
      result = result + "Referer: " + data_.at("referer") + "\r\n";
    }

    if (data_.at("Accept-Encoding") != "") {
      result =result + "Accept-Encoding: " + data_.at("Accept-Encoding")  + "\r\n";
    }

    if (data_.at("Accept-Language") != "") {
      result = result + "Accept-Language: " + data_.at("Accept-Language") + "\r\n";
    }

    if (data_.at("Cookie") != "") {
      result = result + "Cookie: " + data_.at("Cookie") + "\r\n";
    }

    if (data_.at("Content-Type") != "") {
      result = result + "Content-Type: " + data_.at("Content-Type") + "\r\n";
    }

    if (data_.at("Content-Length") != "") {
      result = result + "Content-Length: " + data_.at("Content-Length") + "\r\n";
    }

    if (data_.at("Origin") != "") {
      result = result + "Origin: " + data_.at("Origin") + "\r\n";
    }

    result = result + "\r\n";
    std::vector<char> to_send;
    for (auto c : result) {
      to_send.push_back(c);
    }

    for (auto c : data_to_send_) {
      to_send.push_back(c);
    }

    return to_send;
  }

private:
  std::string GetDataField(std::string src, std::string field) {
    if (src.find(field) == -1) {
      return "";
    }

    int pos = src.find(field);
    pos += strlen(field.c_str());
    std::string result;

    for (size_t i = pos; src[i] != '\r' && src[i] != '\n'; i++) {
      result += src[i];
    }
    return result;
  }

  std::vector<char> data_to_send_;
  std::unordered_map<std::string, std::string> data_;
};

class QueryHandler {
public:
  static Response GetResponse(const Query& query, const FileManager& storage) {
    if (query.GetMethod() == "GET") {
      int status_code;
      Response response;

      auto response_data = storage.Get(query.GetPath(), status_code);
      response.SetVersion("HTTP/1.1");
      response.SetHeadAttr("Content-Type", GetFileType(query.GetPath()));

      response.SetFile(response_data);

      switch (status_code) {
        case 200:
          response.SetStatusCode("200");
          response.SetReasonPhrase("OK");
          break;
        case 404:
          response.SetStatusCode("404");
          response.SetReasonPhrase("Not Found");
          break;
        default:
          UNREACHABLE();
          break;
      }

      return response;
    }

    return Response("");
  }

  static Response GetProxy(const Query& query, FileManager& storage) {
    auto finded = storage.Find(query.GetPackage());
    if (finded.first) {
      Logger::Log("[CACHE] Got from cache.", SERVER);
      return finded.second;
    }

    struct addrinfo addr_hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM
    };
    struct addrinfo *addr_result = NULL;

    Logger::Log(query.GetHost().c_str(), SERVER);
    getaddrinfo(query.GetHost().c_str(), "http", &addr_hints, &addr_result);
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (0 != connect(sock, addr_result->ai_addr, addr_result->ai_addrlen)) {
      Logger::Log(strerror(errno));
      return Response("[SERVER] Server problems.");
    }

    Logger::Log("[SERVER] Loading data in proxy.", SERVER);

    Logger::Log(query.GetBasicPackage().data(), SERVER);
    write(sock, query.GetBasicPackage().data(), query.GetBasicPackage().size());

    char buffer[4096];
    char* input = (char*)malloc(1);
    ssize_t length_input = 0, readed;
    while ((readed = read(sock, buffer, sizeof(buffer))) > 0) {
      input = (char*)realloc(input, length_input + readed + 1);
      memcpy(input + length_input, buffer, readed);
      length_input += readed;
    }
    close(sock);

    Response result;
    std::vector<char> file;
    for (size_t i = 0; i < length_input; ++i) {
      file.push_back(input[i]);
    }
    result.SetFile(file);
    result.JustFile() = true;

    storage.Save(query.GetPackage(), result);
    Logger::Log("[CACHE] Cached.", SERVER);

    return result;
  }

  static void ExtractData(const char buffer[], size_t readed, std::string &header, std::vector<char> &data) {
    size_t count = 0;
    bool flag = false;

    for (size_t i = 0; i < readed; ++i) {
      if (flag) {
        data.push_back(buffer[i]);
      } else {
        header.push_back(buffer[i]);
      }
      if (buffer[i] == '\n' || buffer[i] == '\r') {
        if (buffer[i] == '\n') {
          count++;
        }
      } else {
        count = 0;
      }

      if (count == 2) {
        flag = true;
      }
    }
  }

  static Query RecieveFrom(int client_fd) {
    char buffer[4096];
    int readed = 0;
    readed = read(client_fd, buffer, sizeof(buffer));

    std::vector<char> data;
    std::string header;

    ExtractData(buffer, readed, header, data);

    if (header.find("boundary=----WebKitFormBoundary") != -1) {
      char* input = (char*)malloc(1);
      ssize_t length_input = 0, readed;
      while ((readed = read(client_fd, buffer, sizeof(buffer))) > 0) {
        input = (char*)realloc(input, length_input + readed + 1);
        memcpy(input + length_input, buffer, readed);
        length_input += readed;
      }
      for (int i = 0; i < length_input; ++i) {
        data.push_back(input[i]);
      }

      free(input);
    }

    return Query(header, data);
  }

  static void SendTo(int client_fd, const Response &data = SimpleResponse()) {
    const char *response;
    ssize_t total_cnt, now_cnt;
    if (!data.JustFile()) {
      response = data.GetStr().c_str();
      total_cnt = 0, now_cnt;
      while (total_cnt != strlen(response)) {
        now_cnt = write(client_fd, response + total_cnt, strlen(response) - total_cnt);
        total_cnt += now_cnt;
      }
    }

    auto file = data.GetFile();

    response = file.data();
    total_cnt = 0;
    while (total_cnt != file.size()) {
      now_cnt = write(client_fd, response + total_cnt, file.size() - total_cnt);
      total_cnt += now_cnt;
    }
  }

private:
  static std::string GetFileType(const std::string& file) {
    std::string format;
    for (int i = file.size() - 1; i >= 0; i--) {
      if (file[i] == '.')
        break;
      format += file[i];
    }
    std::reverse(format.begin(), format.end());

    if (format == "ico") {
      return "image/x-icon; charset=UTF-8";
    }

    if (format == "jpg") {
      return "image/png; charset=UTF-8";
    }

    return "text/html; charset=UTF-8";
  }
};


class Connection {
 public:
  Connection() = default;

  Connection(int port);

  static void Handle(int fd, Connection* conn);

  void Accept(std::vector<int> fds);

  FileManager& GetStorage() {
    return storage_;
  }

  ~Connection();

 private:
  int socket_;
  std::string host_;
  FileManager storage_;
};



#endif //WEB_SERVER_CONNECTION_H
