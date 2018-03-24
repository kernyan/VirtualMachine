#include "parser.h"
#include <vector>
#include <iostream>

using std::vector;

void VMParser::operator()(string &LineAsString)
{
  line = LineAsString;
  size_t pos = line.find("//");
  if (pos < line.size()) {
    comment = line.substr(pos, line.size());
    line.replace(pos, line.size(), "");
  }
  vector<string> vs;
  if (!line.empty()) {
    while (true) {
      size_t pos = line.find(" ");
      if (pos < line.size()) {
        vs.push_back(line.substr(size_t (0), pos));
        line.replace(size_t (0), pos + 1, "");
      } else if (line.size() > 1) {
        vs.push_back(line.substr(size_t (0), line.size() - 1));
        break;
      } else {
        break;
      }
    }
  }
  switch (vs.size()) {
  case 0: break;
  case 1: command = command_type::C_ARITHMETIC; break;
  case 2: std::cerr << "Unexpected VM command with only two arguments encountered\n" << vs[1]
          << std::endl; break;
  case 3:
    {
      if (vs[0] == "push")
        command = command_type::C_PUSH;
      else if (vs[0] == "pop")
        command = command_type::C_POP;
      else
        std::cerr <<  "Unexpected memory command encountered\n" << vs[0] << std::endl;

      arg1 = vs[1];
      arg2 = std::stoi(vs[2]);
      break;
    }
  default:
    std::cerr << "Unexpected VM command with more than 3 arguments encountered\n" << vs[3]
      << std::endl; break;
  }
}
