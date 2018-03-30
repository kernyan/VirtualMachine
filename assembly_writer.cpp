#include "assembly_writer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

AssemblyWriter::AssemblyWriter() :
  arithmetic_jumps(alu_command_max)
{
}

void AssemblyWriter::add_line(const string &line)
{
  assembly_strings.push_back(line + "\n");
}

void AssemblyWriter::process_tokens(const ParsedData &data)
{
  switch (data.command) {
  case command_type::C_ARITHMETIC: do_arithmetic(data); break;
  case command_type::C_PUSH: do_push(data); break;
  case command_type::C_POP: do_pop(data); break;
  case command_type::C_COMMENT: do_comment(data); break;
  default:
    std::cerr << "VM Command Type not yet implemented.\n"; break;
  }
}

alu_commands AssemblyWriter::string_to_alu_type(const string &s)
{
  if (s == "add")
    return A_ADD;
  else if (s == "sub")
    return A_SUB;
  else if (s == "neg")
    return A_NEG;
  else if (s == "eq")
    return A_EQ;
  else if (s == "gt")
    return A_GT;
  else if (s == "lt")
    return A_LT;
  else if (s == "and")
    return A_AND;
  else if (s == "or")
    return A_OR;
  else if (s == "not")
    return A_NOT;
  else
    std::cerr << "Unexpected alu_command encountered in string_to_alu\n";
    return alu_commands::A_UNDEFINED;
}

bool AssemblyWriter::segment_need_offset(const string &s)
{
  if (  s == "local"
     || s == "argument"
     || s == "this"
     || s == "that")
     //|| s == "temp"
     //|| s == "pointer")
    return true;
  else
    return false;
}

string AssemblyWriter::get_jump_name(const string &s)
{
  int jump_index = arithmetic_jumps[int (string_to_alu_type(s))]++; 
  string s_up = s;
  std::transform(s_up.begin(), s_up.end(), s_up.begin(), ::toupper);
  return (s_up + "_" + std::to_string(jump_index)); 
}

void AssemblyWriter::alu_add(const ParsedData &data)
{
  add_line("//ADD");
  add_line("@SP");
  add_line("AM=M-1");
  add_line("D=M");
  add_line("A=A-1");
  add_line("M=D+M");
}

void AssemblyWriter::alu_sub(const ParsedData &data)
{
  add_line("//SUB");
  add_line("@SP");
  add_line("AM=M-1");
  add_line("D=M");
  add_line("A=A-1");
  add_line("M=M-D");
}

void AssemblyWriter::alu_neg(const ParsedData &data)
{
  add_line("//NEG");
  add_line("@SP");
  add_line("A=M-1");
  add_line("M=-M");
}

void AssemblyWriter::alu_eq(const ParsedData &data)
{
  string jump_name = get_jump_name("eq");
  add_line("//EQ");
  add_line("@SP");
  add_line("AM=M-1");
  add_line("D=M");
  add_line("A=A-1");
  add_line("M=M-D");
  add_line("D=0");
  add_line("@" + jump_name);
  add_line("M; JEQ");
  add_line("D=1");
  add_line("(" + jump_name + ")");
  add_line("M=D");
}

void AssemblyWriter::alu_gt(const ParsedData &data)
{
  string jump_name = get_jump_name("gt");
  add_line("//GT");
  add_line("@SP");
  add_line("AM=M-1");
  add_line("D=M");
  add_line("A=A-1");
  add_line("M=M-D");
  add_line("D=0");
  add_line("@" + jump_name);
  add_line("M; JGT");
  add_line("D=1");
  add_line("(" + jump_name + ")");
  add_line("M=D");
}

void AssemblyWriter::alu_lt(const ParsedData &data)
{
  string jump_name = get_jump_name("lt");
  add_line("//LT");
  add_line("@SP");
  add_line("AM=M-1");
  add_line("D=M");
  add_line("A=A-1");
  add_line("M=M-D");
  add_line("D=0");
  add_line("@" + jump_name);
  add_line("M; JLT");
  add_line("D=1");
  add_line("(" + jump_name + ")");
  add_line("M=D");
}

void AssemblyWriter::alu_and(const ParsedData &data)
{
  add_line("//AND");
  add_line("@SP");
  add_line("AM=M-1");
  add_line("D=M");
  add_line("A=A-1");
  add_line("M=D&M");
}

void AssemblyWriter::alu_or(const ParsedData &data)
{
  add_line("//OR");
  add_line("@SP");
  add_line("AM=M-1");
  add_line("D=M");
  add_line("A=A-1");
  add_line("M=D|M");
}

void AssemblyWriter::alu_not(const ParsedData &data)
{
  add_line("//NOT");
  add_line("@SP");
  add_line("A=M-1");
  add_line("M=!M");
}

void AssemblyWriter::do_arithmetic(const ParsedData &data)
{
  switch (string_to_alu_type(data.arg1)) {
  case alu_commands::A_ADD: alu_add(data); break;
  case alu_commands::A_SUB: alu_sub(data); break;
  case alu_commands::A_NEG: alu_neg(data); break;
  case alu_commands::A_EQ:  alu_eq(data); break;
  case alu_commands::A_GT:  alu_gt(data); break;
  case alu_commands::A_LT:  alu_lt(data); break;
  case alu_commands::A_AND: alu_and(data); break;
  case alu_commands::A_OR:  alu_or(data); break;
  case alu_commands::A_NOT: alu_not(data); break;
  default:
    std::cerr << "Unexpected alu_command encountered in do_arithmetic\n";
    break;
  }
}

string AssemblyWriter::get_segment_name(const ParsedData &data)
{
  if (data.arg1 == "local") {
    return "LCL";
  } else if (data.arg1 == "argument") {
    return "ARG";
  } else if (data.arg1 == "this") {
    return "THIS";
  } else if (data.arg1 == "that") {
    return "THAT";
  } else if (data.arg1 == "constant") {
    return std::to_string(data.arg2);
  } else if (data.arg1 == "static") {
    return (data.filename + "." + std::to_string(data.arg2));
  } else if (data.arg1 == "temp") {
    return "R" + std::to_string(5 + data.arg2);
  } else if (data.arg1 == "pointer") {
    return "R" + std::to_string(3 + data.arg2);
  } else {
   std::cerr << "Register segment not yet implemented.\n";
   return "";
  }
}

void AssemblyWriter::add_lines_segment_position(const ParsedData &data)
{
  if (segment_need_offset(data.arg1)) {
    if (data.arg2 == 0) {
      add_line("@" + get_segment_name(data));
      add_line("A=M");
    } else {
      add_line("@" + get_segment_name(data));
      add_line("D=M");
      add_line("@" + std::to_string(data.arg2));
      add_line("A=D+A");
    }
  } else {
    add_line("@" + get_segment_name(data));
  }
}

void AssemblyWriter::add_lines_push_sp()
{
  add_line("@SP");
  add_line("M=M+1");
  add_line("A=M-1");
}

void AssemblyWriter::add_lines_pop_sp()
{
  add_line("@SP");
  add_line("AM=M-1");
}

void AssemblyWriter::do_push(const ParsedData &data)
{
  add_line("//push " + data.arg1 + " " + std::to_string(data.arg2) + "");
  add_lines_segment_position(data);
  if (data.arg1 == "constant")
    add_line("D=A");
  else
    add_line("D=M");
  add_lines_push_sp();
  add_line("M=D");
}

void AssemblyWriter::do_pop(const ParsedData &data)
{
  add_line("//pop " + data.arg1 + " " + std::to_string(data.arg2) + "");
  if (segment_need_offset(data.arg1)) {
    add_lines_segment_position(data);
    add_line("D=A");
    add_line("@SegAdd");
    add_line("M=D");
  }
  add_lines_pop_sp();
  add_line("D=M");
  if (segment_need_offset(data.arg1)) {
    add_line("@SegAdd");
    add_line("A=M");
  } else if (  data.arg1 == "static"
            || data.arg1 == "temp"
            || data.arg1 == "pointer") {
    add_lines_segment_position(data);
  } else {
    std::cerr << "Pop of " << data.arg1 << " encountered\n";
  }
  add_line("M=D");
}

void AssemblyWriter::do_comment(const ParsedData &data)
{
  assembly_strings.push_back(data.comment);
}

void AssemblyWriter::write_tofile(const string &FileName)
{
  std::ofstream outFile(FileName);
  if (outFile) {
    for (const auto &Line : assembly_strings) {
      outFile << Line;
    }
  } else {
    std::cerr << "Unable to open output file" << std::endl;
  }
}

