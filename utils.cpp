#include "utils.h"

string infer_output_name(const string &InFile)
{
  string out_file_name = InFile; 
  return out_file_name.replace(out_file_name.end() - 3,
      out_file_name.end(), ".asm");
}
