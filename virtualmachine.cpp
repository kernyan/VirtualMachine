#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "parser.h"
#include "assembly_writer.h"
#include "utils.h"


int main(int argc, char *argv[])
{
  char *filename = argv[argc-1];
  std::ifstream in_file(filename);
  if (in_file) {
    string FileName = replace_string_to_end(filename, 3, ""); // remove .vm extension
    VMParser parser(FileName);
    char opt;
    while ((opt = getopt(argc, argv, "oc")) != -1) {
      switch (opt) {
        case 'o': parser.set_argv_optimize(); break;
        case 'c': parser.set_argv_comments(); break;
        default:
          fprintf(stderr, "Usage: %s [-oc] [file...]\n", argv[0]);
          exit(EXIT_FAILURE);
      }
    }

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
