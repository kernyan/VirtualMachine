#ifndef VIRTUALMACHINE_ASSEMBLY_WRITER_H_
#define VIRTUALMACHINE_ASSEMBLY_WRITER_H_

#include <string>
#include <vector>
using std::string;
using std::vector;

class VMParser; // forward declaration

class AssemblyWriter
{
  vector<string> assembly_strings;

  public:
  AssemblyWriter () {};
  void process_tokens(const VMParser &Parser);
  void write_tofile(const string &FileName);
};

#endif // VIRTUALMACHINE_ASSEMBLY_WRITER_H_


