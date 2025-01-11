#ifndef __MACHINE__
#define __MACHINE__

#include "instruction.cc"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

constexpr int MAX_MEM = 30000;
namespace machine {

class Machine {
public:
  Machine(std::vector<Instruction> &code) : code(code) {}
  void execute() {
    while (ip < code.size()) {
      Instruction ins = code.at(ip);

      switch (ins.type) {
      case InsType::PLUS:
        memory[dp] += ins.argument;
        break;
      case InsType::MINUS:
        memory[dp] -= ins.argument;
        break;
      case InsType::RIGHT:
        dp += ins.argument;
        break;
      case InsType::LEFT:
        dp -= ins.argument;
        break;
      case InsType::READ_CHAR:
        for (int i = 0; i < ins.argument; i++) {

          readChar();
        }
        break;
      case InsType::PUT_CHAR:
        for (int i = 0; i < ins.argument; i++) {

          putChar();
        }
        break;
      case InsType::JUMP_IF_ZERO:
        if (memory[dp] == 0) {
          ip = ins.argument;
          continue;
        }
        break;
      case InsType::JUMP_IF_NOT_ZERO:

        if (memory[dp] != 0) {
          ip = ins.argument;
          continue;
        }
        break;
      }
      ip++;
    }
  }

  inline std::string getOutput() const { return output.str(); }

  int *getMemory() { return memory; }

  // This is for testing purpose
  void setMemoryValue(int pos, int value) { memory[pos] = value; }

private:
  inline void readChar() {
    input >> buf;
    if (input.bad()) {
      throw std::runtime_error{"wrong num bytes read"};
    }
    memory[dp] = (int)buf;
  }

  void putChar() {
    buf = (char)memory[dp];
    output << buf;
    if (input.bad()) {
      throw std::runtime_error{"wrong num bytes read"};
    }
    memory[dp] = (int)buf;
  }

  std::vector<Instruction> code;
  int memory[MAX_MEM]{};
  int ip{}; // Instruction pointer
  int dp{}; // data pointer
  char buf{};
  std::istringstream input;
  std::ostringstream output;
};
} // namespace machine

#endif