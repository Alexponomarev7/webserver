//
// Created by Алексей Пономарев on 2019-05-21.
//

#ifndef WEB_SERVER_FILE_MANAGER_H
#define WEB_SERVER_FILE_MANAGER_H

#include <string>
#include <mutex>
#include <unordered_map>
#include <stdio.h>
#include <utils/logger/logger.h>
#include <server/libs/common/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

class Data {
public:
  Data(char* data, size_t len) : data_(data), len_(len) {}

  void WriteTo(int fd) {
    for (size_t i = 0; i < len_; ++i) {
      write(fd, &data_[i], sizeof(data_[i]));
    }
  }

  ~Data() {
    free(data_);
  }
private:
  size_t len_;
  char* data_;
};

class FileManager {
public:
  FileManager(const std::string& static_root);

  std::vector<char> Get(const std::string& path, int& status_code) const;

  void Save(const std::string& key, Response& resp) {
    auto lock = std::lock_guard(lock_);

    if (cache_.size() == MaxSize_) {
      cache_.erase(cache_.begin());
    }
    cache_[key] = resp;
  }

  std::pair<bool, Response> Find(const std::string& key) {
    auto lock = std::lock_guard(lock_);

    if (cache_.find(key) != cache_.end()) {
      return {true, cache_.find(key)->second};
    }

    return {false, Response("not cached")};
  }

private:
  std::string static_root;
  const size_t MaxSize_ = 1024;
  std::mutex lock_;
  std::unordered_map<std::string, Response> cache_;
};


#endif //WEB_SERVER_FILE_MANAGER_H
