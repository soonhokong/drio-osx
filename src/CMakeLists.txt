cmake_minimum_required(VERSION 2.8.7)
project(DRIO)
set(CMAKE_COLOR_MAKEFILE ON)
include(CTest)
include(ExternalProject)

find_package(GIT REQUIRED)
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

################################################################
# Set Module Path
################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

################################################################
# External: googletest (Google Test)
################################################################
ExternalProject_Add(GTEST
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external
  GIT_REPOSITORY https://github.com/soonhokong/googletest.git
  GIT_TAG origin/master
  UPDATE_COMMAND ${GIT_EXECUTABLE} pull -s recursive -X theirs origin master
  CONFIGURE_COMMAND cmake -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} "-DCMAKE_CXX_FLAGS=${EXTERNAL_CXX_FLAGS} -w" -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR} ./
  BUILD_COMMAND make -j
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
)
set(EXTRA_LIBS ${EXTRA_LIBS} "gtest")

################################################################
# External: set up include dir and libpath
################################################################
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
set(EXTERNAL_LD_FLAGS "-L${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${DRIO_EXTRA_LINKER_FLAGS} ${EXTERNAL_LD_FLAGS}")

################################################################
# Adds executable
################################################################
add_executable(sh main.cpp)
target_link_libraries(sh SH_UTIL formula)

################################################################
# Add tests
################################################################
add_subdirectory(tests/types/formula)

################################################################
# Add Dependencies
################################################################
add_dependencies(formula GTEST)

################################################################
# Include style check
################################################################
include(StyleCheck)
file(GLOB_RECURSE DRIO_SOURCES
  ${DRIO_SOURCE_DIR}/shell/*.cpp      ${DRIO_SOURCE_DIR}/shell/*.h
  ${DRIO_SOURCE_DIR}/types/*.cpp      ${DRIO_SOURCE_DIR}/types/*.h
  ${DRIO_SOURCE_DIR}/tests/*.cpp      ${DRIO_SOURCE_DIR}/tests/*.h
  )
add_style_check_target(style "${DRIO_SOURCES}")
add_test(NAME style_check COMMAND ${DRIO_SOURCE_DIR}/cmake/Modules/cpplint.py ${DRIO_SOURCES})

ADD_CUSTOM_COMMAND(TARGET sh
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory ${DRIO_SOURCE_DIR}/../bin
          COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_BINARY_DIR}/sh ${DRIO_SOURCE_DIR}/../bin/
)
