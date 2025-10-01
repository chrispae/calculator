cmake_minimum_required(VERSION 3.15)

# GoogleTest integration
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(hello_test test_calculator.cpp)
target_link_libraries(hello_test GTest::gtest_main)

include(GoogleTest) # required to use gtest_discover_tests
gtest_discover_tests(hello_test)
