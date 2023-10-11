cmake_minimum_required(VERSION 3.25)
project(calculator_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(calculator_cpp main.cpp Token.cpp Token.h MathParser.cpp MathParser.h Function.cpp Function.h Calculator.cpp Calculator.h)

add_library(cos SHARED ./plugins/cos.cpp "plugins/cos.cpp")

target_link_libraries(calculator_cpp cos)