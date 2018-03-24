#ifndef VIRTUALMACHINE_PARSER_H_
#define VIRTUALMACHINE_PARSER_H_

#include <string>
#include "vm_commands.h"
using std::string;

class VMParser
{
  string line;
  string arg1;
  string comment;
  int arg2;
  command_type command;
  
  public:
  VMParser ()
   : arg2 {0}, command {command_type::C_UNDEFINED} {};
  void operator()(string &LineAsString);
};

#endif // VIRTUALMACHINE_PARSER_H_
 
