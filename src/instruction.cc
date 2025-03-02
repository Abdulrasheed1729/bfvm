#ifndef __INSTRUCTION__
#define __INSTRUCTION__
namespace machine {

enum class InsType : char {
  PLUS = '+',
  MINUS = '-',
  RIGHT = '>',
  LEFT = '<',
  PUT_CHAR = '.',
  READ_CHAR = ',',
  JUMP_IF_ZERO = '[',
  JUMP_IF_NOT_ZERO = ']',
};

struct Instruction {
  InsType type;
  int argument;
};
} // namespace machine
#endif