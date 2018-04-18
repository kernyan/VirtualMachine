#include "parser.h"
#include "utils.h"
#include <vector>
#include <iostream>
#include <limits>
#include <ctype.h>
#include <cassert>

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

bool VMParser::find_token(const string &s, size_t start,
    size_t &i, size_t &j)
{
  int first_space = s.find(" ", start);
  if (first_space < 0) {
    i = start;
    int last_pos = s.size() - 1; // -1 offset for '\0'
    while (last_pos >= (int) start && 
        !isalnum(s[last_pos])) { // to remove special char e.g. CR
      --last_pos;
    }
    if (last_pos < (int) i) {
      return false;
    } else {
      j = last_pos + 1;
      return true;
    }
  } else if (first_space == (int) start) {
    int first_nonspace = s.find_first_not_of(" ", start);
    if (first_nonspace < 0) {
      return false; // terminate as only no token left
    } else {
      while (first_nonspace > (int) start &&
          !isalnum(s[first_nonspace])) {
        --first_nonspace;
      }
      if (first_nonspace == (int) start) {
        return false;
      } else {
        return find_token(s, first_nonspace, i, j);
      }
    }
  } else {
    i = start;
    while (first_space >= (int) start &&
        !isalnum(s[first_space])) {
      --first_space;
    }
    j = first_space + 1; 
    return true;
  }
}

bool VMParser::find_token(size_t start, size_t &i, size_t &j)
{
  return find_token(data.line, start, i, j);
}

void VMParser::store_tokens(vector<string> &vs)
{
  if (!data.line.empty()) {

    size_t i = 0;
    size_t j = 0;
    while (find_token(j, i, j)) {
      vs.push_back(data.line.substr(i, j - i));
      ++j;
    }
  }
}

void VMParser::populate_vmcommands(vector<string> &vs)
{
  switch (vs.size()) {
  case 0: 
    data.command = command_type::C_COMMENT; 
    break;
  case 1: 
    if (vs[0] == "return") {
      data.command = command_type::C_RETURN;
    } else {
      assert(is_arithmetic(vs[0]));
      data.command = command_type::C_ARITHMETIC;
    }
    data.arg1 = vs[0];
    data.arg2 = std::numeric_limits<int>::min(); // invalid number
    break;
  case 2:
    if (vs[0] == "label") {
      data.command = command_type::C_LABEL; 
    } else if (vs[0] == "if-goto") {
      data.command = command_type::C_IF; 
    } else if (vs[0] == "goto") {
      data.command = command_type::C_GOTO;
    } else {
      std::cerr << "Unexpected \"branching\" command encountered\n"
        << vs[0] << " " << vs[1] << std::endl;
    }
    data.arg1 = vs[1];
    data.arg2 = std::numeric_limits<int>::min(); // invalid number
    break;
  case 3:
    if (vs[0] == "push")
      data.command = command_type::C_PUSH;
    else if (vs[0] == "pop")
      data.command = command_type::C_POP;
    else
      std::cerr <<  "Unexpected memory command encountered\n" << vs[0] << std::endl;

    data.arg1 = vs[1];
    data.arg2 = std::stoi(vs[2]);
    break;
  default:
    std::cerr << "Unexpected VM command with more than 3 arguments encountered\n" << vs[3]
      << std::endl; 
    break;
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
