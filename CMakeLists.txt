cmake_minimum_required(VERSION 3.15)
project(calculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

enable_testing()
add_subdirectory(tests)
