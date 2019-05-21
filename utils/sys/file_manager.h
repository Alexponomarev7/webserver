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

class FileManager {
public:
  FileManager(const std::string& static_root);

  std::string Get(const std::string& path, int& status_code) const;

private:
  std::string static_root;
  std::unordered_map<std::string, std::string> cache;
};


#endif //WEB_SERVER_FILE_MANAGER_H
