#include "assembly_writer.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
  std::stringstream ss;
  ss << "push\n";
  assembly_strings.push_back(ss.str());
}

void AssemblyWriter::do_push(const ParsedData &data)
{
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

