#ifndef VIRTUALMACHINE_PARSER_H_
#define VIRTUALMACHINE_PARSER_H_

#include <string>
#include <vector>
#include "vm_commands.h"
using std::string;
using std::vector;

struct ParsedData
{
  string line;
  string arg1;
  string comment;
  string filename;
  string file;
  int arg2;
  command_type command;
  ParsedData ()
   : arg2 {0}, command {command_type::C_UNDEFINED} {};
};

class VMParser
{
  private:
  ParsedData data;
  bool argv_optimize; // command line flag -o for optimized asm
  bool argv_comments; // command line flag -c for commented asm

  void set_line(const string &LineAsString);
  void remove_comment();
  void store_tokens(vector<string> &vs);
  void populate_vmcommands(vector<string> &vs);
  bool find_token(size_t start, size_t &i, size_t &j);
  
  public:
  VMParser() = delete;
  explicit VMParser (const string &FileName);
  void operator()(const string &LineAsString);
  inline ParsedData get_parsed_data();
  void set_argv_optimize() {
    argv_optimize = true;
  }
  void set_argv_comments() {
    argv_comments = true;
  }
  static bool find_token(const string &s,
      size_t start, size_t &i, size_t &j);
};

inline ParsedData VMParser::get_parsed_data()
{
  return data;
}

#endif // VIRTUALMACHINE_PARSER_H_
 
