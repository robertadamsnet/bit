cmake_minimum_required(VERSION 2.8.12)

include_directories(../src)
add_executable(opt-parse opt-parse.cpp ../src/option.cpp)
