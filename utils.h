#ifndef VIRTUALMACHINE_UTILS_H
#define VIRTUALMACHINE_UTILS_H

#include <string>
using std::string;

string infer_output_name(const string &InFile);
string replace_string_to_end(const string &InString, int pos, const string &Append);


#endif // VIRTUALMACHINE_UTILS_H
