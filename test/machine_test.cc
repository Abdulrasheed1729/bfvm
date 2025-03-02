#include "../src/compiler.cc"
#include "../src/machine.cc"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace machine;
using namespace compiler;

TEST(Machine, Increments) {

  std::string input = "+++++";

  Compiler c = Compiler{input};

  std::vector<Instruction> instructions = c.compile();

  Machine m = Machine{instructions};

  m.execute();

  int *memory = m.getMemory();

  ASSERT_EQ(5, memory[0]) << "cell not correctly incremented. Got %d"
                          << memory[0];
}

TEST(Machine, Decrements) {

  std::string input = "++++++++++-----";

  Compiler c = Compiler{input};

  std::vector<Instruction> instructions = c.compile();

  Machine m = Machine{instructions};

  m.execute();

  int *memory = m.getMemory();

  ASSERT_EQ(5, memory[0]) << "cell not correctly decremented. Got %d"
                          << memory[0];
}

TEST(Machine, IncrementingDataPointer) {

  std::string input = "+>++>+++";

  Compiler c = Compiler{input};

  std::vector<Instruction> instructions = c.compile();

  Machine m = Machine{instructions};

  m.execute();

  std::vector<int> expected = {1, 2, 3};

  int *memory = m.getMemory();

  for (int i = 0; i < expected.size(); i++) {

    ASSERT_EQ(expected[i], memory[i])
        << "Wrong value at memory[" << i << "]. " << "Expected: " << expected[i]
        << " Got: " << memory[i];
  }
}

TEST(Machine, DecrementingDataPointer) {

  std::string input = ">>+++<++<+";

  Compiler c = Compiler{input};

  std::vector<Instruction> instructions = c.compile();

  Machine m = Machine{instructions};

  m.execute();

  std::vector<int> expected = {1, 2, 3};

  int *memory = m.getMemory();

  for (int i = 0; i < expected.size(); i++) {

    ASSERT_EQ(expected[i], memory[i])
        << "Wrong value at memory[" << i << "]. " << "Expected: " << expected[i]
        << " Got: " << memory[i];
  }
}

TEST(Machine, HelloWorld) {

  std::string input =
      "++++++++[>++++[>++>+++>+++>+<<<<-]>+> +>->>+[<]<-]>>.>---.+++++++ ..+ "
      "++.>>.<-.<.+++.------.--------.>>+.>++.";

  Compiler c = Compiler{input};

  std::vector<Instruction> instructions = c.compile();

  Machine m = Machine{instructions};
  m.execute();

  std::string output = m.getOutput();

  ASSERT_EQ("Hello World!\n", output)
      << "Wrong value: " << output << " Expected: Hello World!"
      << " Got: " << output;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
