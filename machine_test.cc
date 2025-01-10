#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "machine.cc"
#include "compiler.cc"

using namespace machine;
using namespace compiler;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}



TEST(Machine, Increments) {
  
  std::string input = "+++++";

  Compiler c = Compiler{input};

  std::vector<Instruction> instructions = c.compile();

  Machine m = Machine{instructions};

  m.execute();

  int* memory = m.getMemory();

  ASSERT_EQ(5, memory[0]);

}

TEST(Machine, Decrements) {
  
  std::string input = "++++++++++-----";

  Compiler c = Compiler{input};

  std::vector<Instruction> instructions = c.compile();

  Machine m = Machine{instructions};

  m.execute();

  int* memory = m.getMemory();

  ASSERT_EQ(5, memory[0]);

}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
