cmake_minimum_required(VERSION 3.25)
project(calculator_cpp)

set(CMAKE_CXX_STANDARD 20)
#add_library(cos SHARED ./plugins/cos.cpp)
#add_library(sin SHARED ./plugins/sin.cpp)
#add_library(power SHARED ./plugins/power.cpp)
#add_library(log SHARED ./plugins/log.cpp)
add_executable(calculator_cpp main.cpp Token.cpp Token.h MathParser.cpp MathParser.h Function.cpp Function.h Calculator.cpp Calculator.h )

#target_link_libraries(calculator_cpp power log)