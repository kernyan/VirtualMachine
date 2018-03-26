#ifndef VIRTUALMACHINE_ASSEMBLY_WRITER_H_
#define VIRTUALMACHINE_ASSEMBLY_WRITER_H_

#include "parser.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct ParsedData ; // forward declaration

class AssemblyWriter
{
  vector<string> assembly_strings;

  public:
  AssemblyWriter () {};
  void process_tokens(const ParsedData &data);
  void write_tofile(const string &FileName);
  void do_arithmetic(const ParsedData &data);
  void do_push(const ParsedData &data);
  void do_pop(const ParsedData &data);
  void do_comment(const ParsedData &data);
};

#endif // VIRTUALMACHINE_ASSEMBLY_WRITER_H_


