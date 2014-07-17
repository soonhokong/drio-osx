cmake_minimum_required(VERSION 2.8.7)
project(DRIO)
set(CMAKE_COLOR_MAKEFILE ON)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories("${DRIO_BINARY_DIR}")

set(CMAKE_CXX_FLAGS                "-Wall -Wextra -std=c++11 ${DRIO_EXTRA_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG          "-g -DDRIO_DEBUG -DDRIO_TRACE -fno-inline")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

include_directories("${DRIO_SOURCE_DIR}")
add_subdirectory(types)
add_subdirectory(shell)

# adds executable
add_executable(sh main.cpp)
target_link_libraries(sh SH_UTIL formula)

ADD_CUSTOM_COMMAND(TARGET sh
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory ${DRIO_SOURCE_DIR}/../bin
          COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_BINARY_DIR}/sh ${DRIO_SOURCE_DIR}/../bin/
)
