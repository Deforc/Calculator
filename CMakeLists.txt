cmake_minimum_required(VERSION 3.25)
project(calculator_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(calculator_cpp main.cpp Token.cpp Token.h MathParser.cpp MathParser.h)
