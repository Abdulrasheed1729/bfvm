#include "compiler.cc"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <vector>

using namespace machine;
using namespace compiler;

TEST(Compiler, Compile) {
  std::string input = "+++++"
                      "-----"
                      "+++++"
                      ">>>>>"
                      "<<<<<";

  std::vector<Instruction> expected = {
      {InsType::PLUS, 5},  {InsType::MINUS, 5}, {InsType::PLUS, 5},
      {InsType::RIGHT, 5}, {InsType::LEFT, 5},
  };

  Compiler c = Compiler{input};
  auto actual = c.compile();
  // Check that the sizes match
  ASSERT_EQ(expected.size(), actual.size())
      << "Expected and actual instruction lists have different sizes.";

  // Compare each instruction
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i].type, actual[i].type)
        << "Mismatch at index " << i << ": Expected type "
        << static_cast<int>(expected[i].type) << " but got "
        << static_cast<int>(actual[i].type);

    EXPECT_EQ(expected[i].argument, actual[i].argument)
        << "Mismatch at index " << i << ": Expected argument "
        << expected[i].argument << " but got " << actual[i].argument;
  }
}

TEST(Compiler, CompileLoops) {
  std::string input = "+[+[+]+]+";

  std::vector<Instruction> expected = {
      Instruction{InsType::PLUS, 1}, Instruction{InsType::JUMP_IF_ZERO, 7},
      Instruction{InsType::PLUS, 1}, Instruction{InsType::JUMP_IF_ZERO, 5},
      Instruction{InsType::PLUS, 1}, Instruction{InsType::JUMP_IF_NOT_ZERO, 3},
      Instruction{InsType::PLUS, 1}, Instruction{InsType::JUMP_IF_NOT_ZERO, 1},
      Instruction{InsType::PLUS, 1},
  };

  Compiler c = Compiler{input};
  auto actual = c.compile();

  // Check that the sizes match
  ASSERT_EQ(expected.size(), actual.size())
      << "Expected and actual instruction lists have different sizes.";

  // Compare each instruction
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i].type, actual[i].type)
        << "Mismatch at index " << i << ": Expected type "
        << static_cast<int>(expected[i].type) << " but got "
        << static_cast<int>(actual[i].type);

    EXPECT_EQ(expected[i].argument, actual[i].argument)
        << "Mismatch at index " << i << ": Expected argument "
        << expected[i].argument << " but got " << actual[i].argument;
  }
}

TEST(Compiler, CompileLoopsThrow) {
  std::string input = "+[+[+]++";


  Compiler c = Compiler{input};


  ASSERT_THROW(c.compile(), std::runtime_error);
}

TEST(Compiler, CompileEverything) {
  std::string input = "+++[---[+]>>>]<<<";

  std::vector<Instruction> expected = {
      Instruction{InsType::PLUS, 3},  Instruction{InsType::JUMP_IF_ZERO, 7},
      Instruction{InsType::MINUS, 3}, Instruction{InsType::JUMP_IF_ZERO, 5},
      Instruction{InsType::PLUS, 1},  Instruction{InsType::JUMP_IF_NOT_ZERO, 3},
      Instruction{InsType::RIGHT, 3}, Instruction{InsType::JUMP_IF_NOT_ZERO, 1},
      Instruction{InsType::LEFT, 3},
  };

  Compiler c = Compiler{input};
  auto actual = c.compile();

  // Check that the sizes match
  ASSERT_EQ(expected.size(), actual.size())
      << "Expected and actual instruction lists have different sizes.";

  // Compare each instruction
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i].type, actual[i].type)
        << "Mismatch at index " << i << ": Expected type "
        << static_cast<int>(expected[i].type) << " but got "
        << static_cast<int>(actual[i].type);

    EXPECT_EQ(expected[i].argument, actual[i].argument)
        << "Mismatch at index " << i << ": Expected argument "
        << expected[i].argument << " but got " << actual[i].argument;
  }
}

TEST(Compiler, CompileEverythingThrows) {
  std::string input = "+++[---[+]>>>]<<<";

  std::vector<Instruction> expected = {
      Instruction{InsType::PLUS, 3},  Instruction{InsType::JUMP_IF_ZERO, 7},
      Instruction{InsType::MINUS, 3}, Instruction{InsType::JUMP_IF_ZERO, 5},
      Instruction{InsType::PLUS, 1},  Instruction{InsType::JUMP_IF_NOT_ZERO, 3},
      Instruction{InsType::RIGHT, 3}, Instruction{InsType::JUMP_IF_NOT_ZERO, 1},
      Instruction{InsType::LEFT, 3},
  };

  Compiler c = Compiler{input};
  auto actual = c.compile();

  // Check that the sizes match
  ASSERT_EQ(expected.size(), actual.size())
      << "Expected and actual instruction lists have different sizes.";

  // Compare each instruction
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i].type, actual[i].type)
        << "Mismatch at index " << i << ": Expected type "
        << static_cast<int>(expected[i].type) << " but got "
        << static_cast<int>(actual[i].type);

    EXPECT_EQ(expected[i].argument, actual[i].argument)
        << "Mismatch at index " << i << ": Expected argument "
        << expected[i].argument << " but got " << actual[i].argument;
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
