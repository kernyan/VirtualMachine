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
  vector<int> arithmetic_jumps;
  void do_arithmetic(const ParsedData &data);
  void do_push(const ParsedData &data);
  void do_pop(const ParsedData &data);
  void do_comment(const ParsedData &data);
  void add_line(const string &line);
  void alu_add(const ParsedData &data);
  void alu_sub(const ParsedData &data);
  void alu_neg(const ParsedData &data);
  void alu_eq(const ParsedData &data);
  void alu_gt(const ParsedData &data);
  void alu_lt(const ParsedData &data);
  void alu_and(const ParsedData &data);
  void alu_or(const ParsedData &data);
  void alu_not(const ParsedData &data);
  string get_jump_name(const string &s);

  public:
  AssemblyWriter ();
  void process_tokens(const ParsedData &data);
  void write_tofile(const string &FileName);
  static alu_commands string_to_alu_type(const string &s);
};

#endif // VIRTUALMACHINE_ASSEMBLY_WRITER_H_


