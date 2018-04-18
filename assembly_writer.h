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

  // stack commands
  void do_push(const ParsedData &data);
  void do_pop(const ParsedData &data);
  void add_lines_push_sp();
  void add_lines_pop_sp();

  // arithmetic and logical operations
  void do_arithmetic(const ParsedData &data);
  void alu_add(const ParsedData &data);
  void alu_sub(const ParsedData &data);
  void alu_neg(const ParsedData &data);
  void alu_eq(const ParsedData &data);
  void alu_gt(const ParsedData &data);
  void alu_lt(const ParsedData &data);
  void alu_and(const ParsedData &data);
  void alu_or(const ParsedData &data);
  void alu_not(const ParsedData &data);

  // branching commands
  string get_jump_name(const string &s);
  string get_segment_name(const ParsedData &data);
  void add_lines_segment_position(const ParsedData &data);
  void do_label(const ParsedData &data);
  void do_goto(const ParsedData &data);
  void do_if(const ParsedData &data);

  // miscellaneous
  void do_comment(const ParsedData &data);
  void add_line(const string &line);

  public:
  AssemblyWriter ();
  void process_tokens(const ParsedData &data);
  void write_tofile(const string &FileName);
  static alu_commands string_to_alu_type(const string &s);
  static bool segment_need_offset(const string &s);
};

#endif // VIRTUALMACHINE_ASSEMBLY_WRITER_H_


