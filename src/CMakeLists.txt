cmake_minimum_required(VERSION 2.8.7)
project(DRIO)
set(CMAKE_COLOR_MAKEFILE ON)
include(CTest)
include(ExternalProject)

include_directories("${DRIO_BINARY_DIR}")

set(CMAKE_CXX_FLAGS                "-Wall -Wextra -std=c++11 ${DRIO_EXTRA_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG          "-g -DDRIO_DEBUG -DDRIO_TRACE -fno-inline")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

include_directories("${DRIO_SOURCE_DIR}")
include_directories("${DRIO_SOURCE_DIR}/shell")

################################################################
# Set Module Path
################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(GIT REQUIRED)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(Threads REQUIRED)

################################################################
# Setting Bison and Flex versions
################################################################
EXEC_PROGRAM(${BISON_EXECUTABLE} ARGS --version OUTPUT_VARIABLE BISON_VERSION_STR)
STRING(REGEX REPLACE "([^\n]+).*" "\\1" FIRST_LINE "${BISON_VERSION_STR}")
STRING(REGEX REPLACE ".* ([0-9]+)\\.([0-9]+)(\\.([0-9]+))?" "\\1" BISON_VERSION_MAJOR "${FIRST_LINE}")
STRING(REGEX REPLACE ".* ([0-9]+)\\.([0-9]+)(\\.([0-9]+))?" "\\2" BISON_VERSION_MINOR "${FIRST_LINE}")
MESSAGE( STATUS "BISON_VERSION_MAJOR:  ${BISON_VERSION_MAJOR}" )
MESSAGE( STATUS "BISON_VERSION_MINOR:  ${BISON_VERSION_MINOR}" )

EXEC_PROGRAM(${FLEX_EXECUTABLE} ARGS --version OUTPUT_VARIABLE FLEX_VERSION_STR)
STRING(REGEX REPLACE "([^\n]+).*" "\\1" FIRST_LINE "${FLEX_VERSION_STR}")
STRING(REGEX REPLACE ".* ([0-9]+)\\.([0-9]+)(\\.([0-9]+))?( Apple(.)*)?" "\\1" FLEX_VERSION_MAJOR "${FIRST_LINE}")
STRING(REGEX REPLACE ".* ([0-9]+)\\.([0-9]+)(\\.([0-9]+))?( Apple(.)*)?" "\\2" FLEX_VERSION_MINOR "${FIRST_LINE}")
STRING(REGEX REPLACE ".* ([0-9]+)\\.([0-9]+)(\\.([0-9]+))?( Apple(.)*)?" "\\4" FLEX_VERSION_PATCH "${FIRST_LINE}")
STRING(REGEX MATCH "Apple" FLEX_VERSION_APPLE "${FIRST_LINE}" )
MESSAGE( STATUS "FLEX_VERSION_MAJOR:  ${FLEX_VERSION_MAJOR}" )
MESSAGE( STATUS "FLEX_VERSION_MINOR:  ${FLEX_VERSION_MINOR}" )
MESSAGE( STATUS "FLEX_VERSION_PATCH:  ${FLEX_VERSION_PATCH}" )
MESSAGE( STATUS "FLEX_VERSION_APPLE:  ${FLEX_VERSION_APPLE}" )

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
# Adds subdirectories
################################################################
add_subdirectory(types)
add_subdirectory(shell)

################################################################
# External: set up include dir and libpath
################################################################
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
set(EXTERNAL_LD_FLAGS "-L${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${DRIO_EXTRA_LINKER_FLAGS} ${EXTERNAL_LD_FLAGS}")

# Load dreal libs
ExternalProject_Add(
  dreal
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/
  GIT_REPOSITORY https://github.com/pondering/dreal-weichen.git
  GIT_TAG origin/dreal-api
  UPDATE_COMMAND git pull origin dreal-api
  CONFIGURE_COMMAND rm -rf build && mkdir build && cd build && cmake -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_CXX_FLAGS=-fPIC -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR} ../src
  BUILD_COMMAND cd build && make -j
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND cd build && make install
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/lib/libdreal_api.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/api/libopensmt_api.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/dsolvers/libdsolvers.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libglog.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/egraph/libopensmt_egraph.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/cnfizers/libopensmt_cnfizers.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/common/libopensmt_common.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/tsolvers/libopensmt_tsolvers.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/tsolvers/emptysolver/libopensmt_emptysolver.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/sorts/libopensmt_sorts.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/simplifiers/libopensmt_simplifiers.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/smtsolvers/libopensmt_smtsolvers.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/opensmt/parsers/smt2/libopensmt_smt2parser.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/realpaver/librealpaver.a")


set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapddynset.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libgflags.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdpoincare.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdalglib.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapddynsysfacade.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdvectalg.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdmap.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdgeomset.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapddiffAlgebra.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdcovrel.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libglog.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libgflags_nothreads.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdintervals.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapddynsys.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdrounding.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdbasicalg.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdalgfacade.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libprim.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libjson11.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdmatrixAlgorithms.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libgtest.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapd.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapddiffIncl.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/lib/libcapdauxil.a")
set(DREAL_LIBS ${DREAL_LIBS} "${PROJECT_BINARY_DIR}/external/src/dreal/build/util/libutil.a")
set(DREAL_LIBS ${DREAL_LIBS} "-lpthread")


################################################################
# Adds executable
################################################################
add_executable(sh main.cpp)
add_dependencies(sh dreal)
target_link_libraries(sh SH_UTIL)
target_link_libraries(sh ${DREAL_LIBS})

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
list(REMOVE_ITEM DRIO_SOURCES ${DRIO_SOURCE_DIR}/shell/FlexLexer/FlexLexer.h ${DRIO_SOURCE_DIR}/shell/FlexLexer/FlexLexer_osx.h)
add_style_check_target(style "${DRIO_SOURCES}")
add_test(NAME style_check COMMAND ${DRIO_SOURCE_DIR}/cmake/Modules/cpplint.py ${DRIO_SOURCES})

################################################################
# Moving compiled shell to bin/sh
################################################################
ADD_CUSTOM_COMMAND(TARGET sh
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory ${DRIO_SOURCE_DIR}/../bin
          COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_BINARY_DIR}/sh ${DRIO_SOURCE_DIR}/../bin/
)
