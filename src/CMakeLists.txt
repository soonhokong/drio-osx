cmake_minimum_required(VERSION 2.8.7)
project(DRIO)
set(CMAKE_COLOR_MAKEFILE ON)

find_package(BISON)
find_package(FLEX)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -O0 -g -Wall -std=c++11 -Wno-deprecated-register")

include_directories("${DRIO_SOURCE_DIR}/shell")
add_subdirectory(shell)

link_directories("${DRIO_BINARY_DIR}/shell")
include_directories("${DRIO_BINARY_DIR}/shell")

# adds executable
add_executable(sh main.cpp)
target_link_libraries(sh SH_UTIL)

ADD_CUSTOM_COMMAND(TARGET sh
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory ${DRIO_SOURCE_DIR}/../bin
          COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_BINARY_DIR}/sh ${DRIO_SOURCE_DIR}/../bin/
)