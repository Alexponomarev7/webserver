//
// Created by Алексей Пономарев on 2019-05-20.
//

#include "cmdparser.h"
#include <utils/sys/helpers.h>

CmdParser::CmdParser(int argc, char **argv) {
  for (size_t i = 1; i < argc; ++i) {
    items_.insert(std::string(argv[i]));
  }
}

CmdParser CmdParser::AddOption(std::string name, std::vector<std::string> option, PARSER type) {
  bool finded = false;
  std::string dest;

  UNUSED(type);

  for (auto opt : option) {
    if (items_.find(opt) != items_.end()) {
      if (finded) {
        throw std::runtime_error("Two required args.");
      }
      finded = true;
      dest = opt;
    }
  }

  replace_[name] = dest;
  return *this;
}

std::string CmdParser::Get(std::string name) {
  return replace_[name];
}