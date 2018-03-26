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
  int arg2;
  command_type command;
  ParsedData ()
   : arg2 {0}, command {command_type::C_UNDEFINED} {};
};

class VMParser
{
  ParsedData data;
  void set_line(const string &LineAsString);
  void remove_comment();
  void store_tokens(vector<string> &vs);
  void populate_vmcommands(vector<string> &vs);
  
  public:
  VMParser () {};
  void operator()(const string &LineAsString);
  inline ParsedData get_parsed_data();
};

inline ParsedData VMParser::get_parsed_data()
{
  return data;
}

#endif // VIRTUALMACHINE_PARSER_H_
 
