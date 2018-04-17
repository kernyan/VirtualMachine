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
    string FileName = replace_string_to_end(argv[1], 3, ""); // remove .vm extension
    VMParser parser(FileName);
    if (argv[2] && argv[2] == std::string("-l"))
      parser.set_local_flag(); 
    AssemblyWriter writer;
    string out_file_name = replace_string_to_end(argv[1], 3, ".asm");
    string line;
    while (std::getline(in_file, line)) {
      parser(line);
      writer.process_tokens(parser.get_parsed_data());
      writer.write_tofile(out_file_name);
    }
  } else {
    std::cerr << "No file name passed in." << std::endl;
  }

  return 0;
}
