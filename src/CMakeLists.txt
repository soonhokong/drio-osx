cmake_minimum_required(VERSION 2.8.7)
project(DRIO)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE on)

find_package(BISON)
find_package(FLEX)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -O0 -g -Wall -std=c++11 -Wno-deprecated-register")

include_directories("${DRIO_SOURCE_DIR}/shell")
set(SH_LIBS ${SH_LIBS} SH_UTIL)
add_subdirectory(shell)

add_executable(shell main.cpp)
target_link_libraries(shell ${SH_LIBS})

ADD_CUSTOM_COMMAND(TARGET shell
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory ${DRIO_SOURCE_DIR}/../bin
          COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_BINARY_DIR}/shell ${DRIO_SOURCE_DIR}/../bin/
)