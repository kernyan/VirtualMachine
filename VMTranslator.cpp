#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"
#include "assembly_writer.h"
#include "utils.h"


int main(int argc, char *argv[])
{
  std::ifstream in_file(argv[1]);
  if (in_file) {
    VMParser parser;
    AssemblyWriter writer;
    string out_file_name = infer_output_name(argv[1]);
    string line;
    while (std::getline(in_file, line)) {
      parser(line);
      writer.process_tokens(parser);
      writer.write_tofile(out_file_name);
    }
  } else {
    std::cerr << "No file name passed in." << std::endl;
  }

  return 0;
}
