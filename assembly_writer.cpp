#include "assembly_writer.h"
#include <iostream>
#include <fstream>
#include <sstream>

void AssemblyWriter::process_tokens(const VMParser &Parser)
{
  for (int i = 0; i < 2; ++i) {
    std::stringstream line;
    line << "Testing " << i << std::endl;
    assembly_strings.push_back(line.str());
  }
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

