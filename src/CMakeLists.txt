cmake_minimum_required(VERSION 2.8.12)

set(bit-common option.cpp db.cpp record.cpp)

add_executable(bit        ${bit-common}  bit.cpp)
add_executable(bit-test   ${bit-common}  bit-test.cpp)
add_executable(bit-init   ${bit-common}  bit-init.cpp)
add_executable(bit-add    ${bit-common}  bit-add.cpp)


