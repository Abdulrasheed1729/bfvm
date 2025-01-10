cmake_minimum_required(VERSION 3.16)

project(bfvm_test)

# Requirements for Google Test
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	compiler_test
	compiler_test.cc
	compiler.cc
	machine.cc
)

add_executable(
	machine_test
	machine_test.cc
	compiler.cc
	machine.cc
)

target_link_libraries(
	compiler_test
	GTest::gtest
	GTest::gtest_main
)

target_link_libraries(
	machine_test
	GTest::gtest
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(compiler_test)
gtest_discover_tests(machine_test)
