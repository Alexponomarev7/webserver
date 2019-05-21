//
// Created by Алексей Пономарев on 2019-05-21.
//

#ifndef WEB_SERVER_FILE_MANAGER_H
#define WEB_SERVER_FILE_MANAGER_H

#include <cstring>
#include <mutex>
#include <unordered_map>
#include <stdio.h>
#include <utils/logger/logger.h>
#include <server/libs/common/types.h>
#include <string>

class FileManager {
public:
  FileManager(const std::string& static_root);

  std::string Get(const std::string& path, int& status_code) const;

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
