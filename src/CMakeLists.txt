cmake_minimum_required(VERSION 2.8.12)

find_package(Boost REQUIRED COMPONENTS filesystem system)


link_directories(${Boost_LIBRARY_DIR})
include_directories(~/options/include)

set(bit-sources 
  bit.cpp 
  cmd-init.cpp
  cmd-build.cpp
  cmd-set.cpp
  cmd-unset.cpp
  db.cpp
  config.cpp
)

add_executable(bit        ${bit-sources})
target_link_libraries(bit ${Boost_LIBRARIES})

#add_executable(bit-test   ${bit-common}  bit-test.cpp)
#add_executable(bit-init   ${bit-common}  bit-init.cpp)
#target_link_libraries(bit-init ${Boost_LIBRARIES})

#add_executable(bit-build   ${bit-common}  bit-build.cpp)
#target_link_libraries(bit-build ${Boost_LIBRARIES})

#add_executable(bit-add    ${bit-common}  bit-add.cpp)


