cmake_minimum_required(VERSION 2.8.12)

set(bit-common options.cpp db.cpp)
include_directories(~/src/csv)

add_executable(bit        ${bit-common}  bit.cpp)
add_executable(bit-init   ${bit-common}  bit-init.cpp)
add_executable(bit-add    ${bit-common}  bit-add.cpp)


