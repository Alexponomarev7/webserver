//
// Created by Алексей Пономарев on 2019-05-05.
//

#ifndef WEB_SERVER_CONFIG_H
#define WEB_SERVER_CONFIG_H

#include <sys/time.h>
#include <sys/resource.h>
#include <unordered_map>

namespace Daemon {

class Config {
 public:
  Config() = default;

  static Config LoadConfig(std::string path_to_config);

  size_t Get(std::string key) const;

  static void SetFdLimit(rlim_t MaxFd);

 private:
  std::unordered_map<std::string, size_t> data_;
};

}

#endif //WEB_SERVER_CONFIG_H
