# VirtualMachine
Hack virtual machine

# Summary
VM program that translates virtual machine (stack architecture) commands to assembly

# VM memory mapping

| RAM index  | Segment                  |
|-----------:|:-------------------------|
|          0 | SP  - Stack pointer      |
|          1 | LCL - Local              |
|          2 | ARG - Arguments          |
|          3 | THIS                     |
|          4 | THAT                     |
|   5 -   12 | Temp segment             |
|  13 -   15 | General purpose registers|
|  16 -  255 | Static variables         |
| 256 - 2047 | Stack                    |

# Implementation
1. Parser - parses the VM commands
2. Writer - produces assembly from parsed VM commands
3. Main   - progam that takes in file.vm and outputs file.asm

# Tasks performed
## Arithmetic/Logical commands
1. add - Adding two values
2. sub - Subtracts two values
3. neg - Negates value on stack
4. eq  - True if top two values on stack are equal
5. gt  - True if second value on stack is greater than top value on stack
6. lt  - True if second value on stack is less than top value on stack
7. and - True only if top two values on stack are non zero
8. or  - True if any of the top two values on stack are non zero
9. not - Negates boolean value on top of stack

## Memory access commands
1. pop *segment* *index*
2. push *segment* *index*
