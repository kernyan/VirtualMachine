#include "parser.h"
#include "utils.h"
#include <vector>
#include <iostream>
#include <limits>

using std::vector;

VMParser::VMParser(const string &FileName) :
  compile_local (false)
{
  data.filename = FileName;
  size_t found = FileName.find_last_of("/");
  data.file = FileName.substr(found + 1);
}

void VMParser::set_line(const string &LineAsString)
{
  data.line = LineAsString;
}

void VMParser::remove_comment()
{
  size_t pos = data.line.find("//");
  if (pos < data.line.size()) {
    string Comment = data.line.substr(pos, data.line.size());
    data.comment = replace_string_to_end(Comment, 1, "\n"); // replace ^M with \n
    data.line.replace(pos, data.line.size(), "");
  }
}

void VMParser::store_tokens(vector<string> &vs)
{
  if (!data.line.empty()) {
    size_t offset = 0;
    if (compile_local)
      offset = 1;
    while (true) {
      size_t pos = data.line.find(" ");
      if (pos < data.line.size()) {
        vs.push_back(data.line.substr(size_t (0), pos));
        data.line.replace(size_t (0), pos + 1, "");
      } else if (data.line.size() > offset) {
        // last entry in string is '\r' character
        vs.push_back(data.line.substr(size_t (0), data.line.size() - offset));
        break;
      } else {
        break;
      }
    }
  }
}

void VMParser::populate_vmcommands(vector<string> &vs)
{
  switch (vs.size()) {
  case 0: data.command = command_type::C_COMMENT; 
          break;
  case 1: data.command = command_type::C_ARITHMETIC;
          data.arg1 = vs[0];
          data.arg2 = std::numeric_limits<int>::min(); // invalid number
          break;
  case 2: std::cerr << "Unexpected VM command with only two arguments encountered\n" << vs[0] << vs[1] << std::endl << data.line
          << std::endl; break;
  case 3:
    {
      if (vs[0] == "push")
        data.command = command_type::C_PUSH;
      else if (vs[0] == "pop")
        data.command = command_type::C_POP;
      else
        std::cerr <<  "Unexpected memory command encountered\n" << vs[0] << std::endl;

      data.arg1 = vs[1];
      data.arg2 = std::stoi(vs[2]);
      break;
    }
  default:
    std::cerr << "Unexpected VM command with more than 3 arguments encountered\n" << vs[3]
      << std::endl; break;
  }
}

void VMParser::operator()(const string &LineAsString)
{
  set_line(LineAsString);
  remove_comment();
  vector<string> vs;
  store_tokens(vs);
  populate_vmcommands(vs);
}
