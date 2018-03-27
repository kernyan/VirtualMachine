#ifndef VIRTUALMACHINE_VM_COMMANDS_H_
#define VIRTUALMACHINE_VM_COMMANDS_H_

enum class command_type
{
  C_UNDEFINED,
  C_COMMENT,
  C_ARITHMETIC,
  C_PUSH,
  C_POP,
  C_LABEL,
  C_GOTO,
  C_IF,
  C_FUNCTION,
  C_RETURN,
  C_CALL
};


enum alu_commands
{
  A_UNDEFINED = 0,
  A_ADD,
  A_SUB,
  A_NEG,
  A_EQ,
  A_GT,
  A_LT,
  A_AND,
  A_OR,
  A_NOT
};

constexpr int alu_command_max = A_NOT;
#endif // VIRTUALMACHINE_VM_COMMANDS_H_
