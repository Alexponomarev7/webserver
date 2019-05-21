//
// Created by Алексей Пономарев on 2019-05-21.
//

#include "file_manager.h"

FileManager::FileManager(const std::string &static_root) : static_root(static_root) {}

std::string FileManager::Get(const std::string &path, int& status_code) const {
  static char buffer[4096];

  const std::string& res_path = static_root + path;

  FILE* file = fopen(res_path.c_str(), "r");
  if (file == NULL) {
    status_code = 404;

    Logger::Log(strerror(errno), SERVER);
    return "Not such file.";
  }

  char* input = (char*)malloc(1);
  size_t length_input = 0, readed;
  while ((readed = fread(buffer, 1, sizeof(buffer), file)) > 0) {
    input = (char *) realloc(input, length_input + readed + 1);
    memcpy(input + length_input, buffer, readed);
    length_input += readed;
  }
  *(input + length_input) = '\0';

  fclose(file);

  status_code = 200;
  return std::string(input);
}