#Custon command for flex/bison

################################################################
# Setting correct parser file based on bison version
################################################################
if ("${BISON_VERSION_MAJOR}" EQUAL 2 AND "${BISON_VERSION_MINOR}" GREATER 3)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${DRIO_BINARY_DIR}/shell/parser.yy
        COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_SOURCE_DIR}/shell/parser/parser_2.yy ${DRIO_BINARY_DIR}/shell/parser.yy
    )
else ("${BISON_VERSION_MAJOR}" EQUAL 2 AND "${BISON_VERSION_MINOR}" GREATER 3)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${DRIO_BINARY_DIR}/shell/parser.yy
        COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_SOURCE_DIR}/shell/parser/parser_2.yy ${DRIO_BINARY_DIR}/shell/parser.yy
    )
endif ("${BISON_VERSION_MAJOR}" EQUAL 2 AND "${BISON_VERSION_MINOR}" GREATER 3)


################################################################
# Execute bison command
################################################################
ADD_CUSTOM_COMMAND(
    OUTPUT ${DRIO_BINARY_DIR}/shell/parser.tab.cc
    COMMAND ${BISON_EXECUTABLE}
    ARGS -d -v ${DRIO_BINARY_DIR}/shell/parser.yy
    DEPENDS ${DRIO_BINARY_DIR}/shell/parser.yy
    DEPENDS ${DRIO_SOURCE_DIR}/shell/scanner.l
    )

################################################################
# Execute flex command
################################################################
ADD_CUSTOM_COMMAND(
    OUTPUT ${DRIO_BINARY_DIR}/shell/lexer.yy.cc
    COMMAND ${FLEX_EXECUTABLE}
    ARGS --outfile=${DRIO_BINARY_DIR}/shell/lexer.yy.cc ${DRIO_SOURCE_DIR}/shell/scanner.l
    DEPENDS ${DRIO_SOURCE_DIR}/shell/scanner.l
    )


################################################################
# Mark custom command results as generated and include in source
################################################################
SET(DRIO_SRCS ${DRIO_SRCS} ${DRIO_BINARY_DIR}/shell/parser.tab.cc)
SET_SOURCE_FILES_PROPERTIES(${DRIO_BINARY_DIR}/shell/parser.tab.cc GENERATED)

INCLUDE_DIRECTORIES(${DRIO_BINARY_DIR}/shell)
add_library(SH_UTIL STATIC lexer.yy.cc parser.tab.cc driver.cpp var_scoped_env.cpp fmla_scoped_env.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare")
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-null-conversion -Wno-unneeded-internal-declaration -Wno-deprecated-register")
endif ()
