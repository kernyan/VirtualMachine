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
  add_line("//GT");
}

void AssemblyWriter::alu_lt(const ParsedData &data)
{
  add_line("//LT");
}

void AssemblyWriter::alu_and(const ParsedData &data)
{
  add_line("//AND");
}

void AssemblyWriter::alu_or(const ParsedData &data)
{
  add_line("//OR");
}

void AssemblyWriter::alu_not(const ParsedData &data)
{
  add_line("//NOT");
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

void AssemblyWriter::do_push(const ParsedData &data)
{
  string TempRegister;
  if (data.arg1 == "local") {
    TempRegister = "LCL";
  } else if (data.arg1 == "argument") {
    TempRegister = "ARG";
  } else if (data.arg1 == "this") {
    TempRegister = "THIS";
  } else if (data.arg1 == "that") {
    TempRegister = "THAT";
  } else if (data.arg1 == "constant") {
    TempRegister = std::to_string(data.arg2);
  } else {
   std::cerr << "Register segment not yet implemented.\n";
  }

  add_line("//push " + data.arg1 + " " + std::to_string(data.arg2) + "");
  add_line("@" + TempRegister);
  add_line("D=A");
  add_line("@SP");
  add_line("A=M");
  add_line("M=D");
  add_line("@SP");
  add_line("M=M+1");
}

void AssemblyWriter::do_pop(const ParsedData &data)
{
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

