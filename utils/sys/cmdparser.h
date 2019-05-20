//
// Created by Алексей Пономарев on 2019-05-20.
//

#ifndef WEB_SERVER_CMDPARSER_H
#define WEB_SERVER_CMDPARSER_H

#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>

enum PARSER {
  REQUIRED_ARG,
  OPTIONAL_ARG,
};

class Option {
public:
  Option(PARSER type, std::vector<std::string> args) {

  }

private:
};

class CmdParser {
public:
  CmdParser(int argc, char* argv[]);

  CmdParser AddOption(std::string name, std::vector<std::string> option, PARSER type);

  std::string Get(std::string name);
private:
  std::unordered_map<std::string, std::string> replace_;
  std::set<std::string> items_;
};


#endif //WEB_SERVER_CMDPARSER_H
