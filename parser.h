#ifndef VIRTUALMACHINE_PARSER_H_
#define VIRTUALMACHINE_PARSER_H_

#include <string>
using std::string;

class VMParser
{
  string line;
  
  public:
  VMParser () {};
  void operator()(string &LineAsString);
};

#endif // VIRTUALMACHINE_PARSER_H_
 
