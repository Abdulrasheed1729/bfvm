#include "compiler.cc"
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>

int main(int argc, char **argv) {
  char *fileName = argv[1];

  std::ifstream code(fileName);
  const std::string content((std::istreambuf_iterator<char>(code)),
                            std::istreambuf_iterator<char>());
  try {
    compiler::Compiler c = compiler::Compiler{content};
    std::vector<machine::Instruction> instructions = c.compile();
    machine::Machine m = machine::Machine{instructions};
    m.execute();

    std::cout << m.getOutput() << "\n";
  } catch (std::runtime_error error) {
    std::cout << error.what() << std::endl;
  }
}
