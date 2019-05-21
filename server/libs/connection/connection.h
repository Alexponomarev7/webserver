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

 private:
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
    auto finded = storage.Find(query.GetHost() + query.GetPath());
    if (finded.first) {
      Logger::Log("[CACHE] Got from cache.", SERVER);
      return finded.second;
    }

    struct addrinfo addr_hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM
    };
    struct addrinfo *addr_result = NULL;

    getaddrinfo(query.GetHost().c_str(), "http", &addr_hints, &addr_result);
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (0 != connect(sock, addr_result->ai_addr, addr_result->ai_addrlen)) {
      Logger::Log(strerror(errno));
      return Response("Server problems.");
    }

    char request[4096];
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\n"
             "Host: %s\n"
             "Connection: close\n"
             "\n",
             query.GetPath().c_str(), query.GetHost().c_str());
    write(sock, request, strnlen(request, sizeof(request)));

    char buffer[4096];
    char* input = (char*)malloc(1);
    size_t length_input = 0, readed;
    while ((readed = read(sock, buffer, sizeof(buffer))) > 0) {
      input = (char*)realloc(input, length_input + readed + 1);
      memcpy(input + length_input, buffer, readed);
      length_input += readed;
    }
    close(sock);

    Response result;
    result.SetPackage(input);

    storage.Save(query.GetHost() + query.GetPath(), result);
    Logger::Log("[CACHE] Cached.", SERVER);

    return result;
  }

  static Query RecieveFrom(int client_fd) {
    static char buffer[4096];

    Query result;

    while (read(client_fd, buffer, sizeof(buffer)) == -1);
    Logger::Log(buffer, SERVER);

    char type[50], path[50], prtcl[50], host[50], connect[50];

    sscanf(buffer, "%s %s %s\n"
                   "Host: %s\n"
                   "Connection: %s", type, path, prtcl, host, connect);

    result.SetMethod(std::string(type));
    result.SetPath(std::string(path));
    result.SetHost(std::string(host));

    return result;
  }

  static void SendTo(int client_fd, const Response &data = SimpleResponse()) {
    const char * response = data.GetStr().c_str();
    ssize_t total_cnt = 0, now_cnt;
    while (total_cnt != strlen(response)) {
      now_cnt = write(client_fd, response + total_cnt, strlen(response) - total_cnt);
      total_cnt += now_cnt;
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
