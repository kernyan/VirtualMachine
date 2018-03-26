#include "assembly_writer.h"
#include <iostream>
#include <fstream>
#include <sstream>

void AssemblyWriter::add_line(const string &line)
{
  assembly_strings.push_back(line);
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

void AssemblyWriter::do_arithmetic(const ParsedData &data)
{
  add_line("//ADD\n");
  add_line("@SP\n");
  add_line("AM=M-1\n");
  add_line("D=M\n");
  add_line("A=A-1\n");
  add_line("M=D+M\n");
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

  add_line("//push " + data.arg1 + " " + std::to_string(data.arg2) + "\n");
  add_line("@" + TempRegister + "\n");
  add_line("D=A\n");
  add_line("@SP\n");
  add_line("A=M\n");
  add_line("M=D\n");
  add_line("@SP\n");
  add_line("M=M+1\n");
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

