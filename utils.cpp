#include "utils.h"

string infer_output_name(const string &InFile)
{
  string out_file_name = InFile; 
  return out_file_name.replace(out_file_name.end() - 3,
      out_file_name.end(), ".asm");
}

string replace_string_to_end(const string &InString, int pos, const string &Append)
{
  string outString = InString; 
  return outString.replace(outString.end() - pos,
      outString.end(), Append);
}
