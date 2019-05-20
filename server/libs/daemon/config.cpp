//
// Created by Алексей Пономарев on 2019-05-05.
//

#include <stdexcept>
#include <string>

#include "config.h"

namespace Daemon {

Config Config::LoadConfig(std::string path_to_config) {
  Config cfg;

  FILE* file = fopen(path_to_config.c_str(), "r");

  if (file == NULL) {
    throw std::runtime_error("not such config.");
  }

  char buffer[1024];

  std::string name;
  size_t value;
  while (fscanf(file, "%s = %d", buffer, &value) != -1) {
    name = std::string(buffer);
    cfg.data_[name] = value;
  }

  fclose(file);

  return cfg;
}

size_t Config::Get(std::string key) const {
  return data_.at(key);
}

void Config::SetFdLimit(rlim_t MaxFd) {
  rlimit lim = {
    .rlim_cur = MaxFd,
    .rlim_max = MaxFd
  };

  if (setrlimit(RLIMIT_NOFILE, &lim)) {
    throw std::runtime_error("[DAEMON] Failed to set fd limit");
  }
}

}