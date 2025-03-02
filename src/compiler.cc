#ifndef __COMPILER__
#define __COMPILER__

#include "./instruction.cc"
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>


namespace compiler {
class Compiler {
public:
  Compiler(std::string code) : code(code) { codeLength = code.length(); }

  std::vector<machine::Instruction> compile() {
    std::stack<int> loopStack;
    while (position < codeLength) {
      char current = code[position];

      switch (current) {
      case '+':
        compileFoldableInstruction('+', machine::InsType::PLUS);
        break;
      case '-':
        compileFoldableInstruction('-', machine::InsType::MINUS);
        break;
      case '<':
        compileFoldableInstruction('<', machine::InsType::LEFT);
        break;
      case '>':
        compileFoldableInstruction('>', machine::InsType::RIGHT);
        break;
      case '.':
        compileFoldableInstruction('.', machine::InsType::PUT_CHAR);
        break;
      case ',':
        compileFoldableInstruction(',', machine::InsType::READ_CHAR);
        break;
      case '[': {
        int insPos = emitWithArgs(machine::InsType::JUMP_IF_ZERO, 0);
        loopStack.push(insPos);
        break;
      }
      case ']': {

        if (loopStack.empty()) {
          throw std::runtime_error("Mismatched ']' at position " +
                                   std::to_string(position));
        }

        int openInsPos = loopStack.top();
        loopStack.pop();
        int closeInsPos =
            emitWithArgs(machine::InsType::JUMP_IF_NOT_ZERO, openInsPos);
        instructions[openInsPos].argument = closeInsPos;
        break;
      }
      }

      position++;
    }

    if (!loopStack.empty()) {
      throw std::runtime_error("Mismatched '[' at position " +
                               std::to_string(loopStack.top()));
    }

    return instructions;
  }

private:
  int emitWithArgs(machine::InsType insType, int arg) {
    machine::Instruction ins = machine::Instruction{insType, arg};
    instructions.push_back(ins);
    return instructions.size() - 1;
  }

  void compileFoldableInstruction(char c, machine::InsType insType) {
    int count = 1;
    while (position < codeLength - 1 && code[position + 1] == c) {
      count += 1;
      position++;
    }
    emitWithArgs(insType, count);
  }

  std::string code;
  int codeLength;
  int position{};
  std::vector<machine::Instruction> instructions{};
};
} // namespace compiler
#endif
