#Custon command for flex/bison

################################################################
# Setting correct parser file based on bison version
################################################################
if ("${BISON_VERSION_MAJOR}" EQUAL 2 AND  NOT ("${BISON_VERSION_MINOR}" LESS 3))
    ADD_CUSTOM_COMMAND(
        OUTPUT ${DRIO_BINARY_DIR}/shell/parser.yy
        COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_SOURCE_DIR}/shell/parser/parser_2.yy ${DRIO_BINARY_DIR}/shell/parser.yy
    )
elseif("${BISON_VERSION_MAJOR}" GREATER 2)
        ADD_CUSTOM_COMMAND(
        OUTPUT ${DRIO_BINARY_DIR}/shell/parser.yy
        COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_SOURCE_DIR}/shell/parser/parser_3.yy ${DRIO_BINARY_DIR}/shell/parser.yy
    )
else ("${BISON_VERSION_MAJOR}" EQUAL 2 AND "${BISON_VERSION_MINOR}" GREATER 3)
    MESSAGE(FATAL_ERROR "Bison version 2.3 or above required. You are using " ${BISON_VERSION_MAJOR} "." ${BISON_VERSION_MINOR})
endif ()

################################################################
# Execute bison command
################################################################
ADD_CUSTOM_COMMAND(
    OUTPUT ${DRIO_BINARY_DIR}/shell/parser.tab.cc
    COMMAND "${BISON_EXECUTABLE}"
    ARGS -d -v ${DRIO_BINARY_DIR}/shell/parser.yy
    DEPENDS ${DRIO_BINARY_DIR}/shell/parser.yy
    DEPENDS ${DRIO_SOURCE_DIR}/shell/scanner.l
    )

################################################################
# Checking which version of FlexLexer to use
################################################################
if(FLEX_VERSION_APPLE STREQUAL "Apple")
    ADD_CUSTOM_COMMAND(
        OUTPUT ${DRIO_BINARY_DIR}/shell/FlexLexer.h
        COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_SOURCE_DIR}/shell/FlexLexer/FlexLexer_osx.h ${DRIO_BINARY_DIR}/shell/FlexLexer.h
    )
elseif(UNIX)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${DRIO_BINARY_DIR}/shell/FlexLexer.h
        COMMAND ${CMAKE_COMMAND} -E copy ${DRIO_SOURCE_DIR}/shell/FlexLexer/FlexLexer.h ${DRIO_BINARY_DIR}/shell/FlexLexer.h
    )
endif()

################################################################
# Checking Flex version
################################################################
if(${FLEX_VERSION_MAJOR} EQUAL 2)
    if(${FLEX_VERSION_MINOR} EQUAL 5)
        if(${FLEX_VERSION_PATCH} LESS 35)
            MESSAGE(FATAL_ERROR "Flex version 2.5.35 or above required. You are using " ${FLEX_VERSION_MAJOR} "." ${FLEX_VERSION_MINOR} "." ${FLEX_VERSION_PATCH})
        endif()
    elseif(${FLEX_VERSION_MINOR} LESS 5)
        MESSAGE(FATAL_ERROR "Flex version 2.5.35 or above required. You are using " ${FLEX_VERSION_MAJOR} "." ${FLEX_VERSION_MINOR} "." ${FLEX_VERSION_PATCH})
    endif()
elseif(${FLEX_VERSION_MAJOR} LESS 2)
    MESSAGE(FATAL_ERROR "Flex version 2.5.35 or above required. You are using " ${FLEX_VERSION_MAJOR} "." ${FLEX_VERSION_MINOR} "." ${FLEX_VERSION_PATCH})
endif()

################################################################
# Execute flex command
################################################################
ADD_CUSTOM_COMMAND(
    OUTPUT ${DRIO_BINARY_DIR}/shell/lexer.yy.cc
    COMMAND ${FLEX_EXECUTABLE}
    ARGS --outfile=${DRIO_BINARY_DIR}/shell/lexer.yy.cc ${DRIO_SOURCE_DIR}/shell/scanner.l
    DEPENDS ${DRIO_SOURCE_DIR}/shell/scanner.l
    DEPENDS ${DRIO_BINARY_DIR}/shell/FlexLexer.h
    DEPENDS ${DRIO_SOURCE_DIR}/types/formula/term.h
    DEPENDS ${DRIO_SOURCE_DIR}/types/formula/formula.h
    )

################################################################
# Mark custom command results as generated and include in source
################################################################
SET(DRIO_SRCS ${DRIO_SRCS} ${DRIO_BINARY_DIR}/shell/parser.tab.cc)
SET_SOURCE_FILES_PROPERTIES(${DRIO_BINARY_DIR}/shell/parser.tab.cc GENERATED)

INCLUDE_DIRECTORIES(${DRIO_BINARY_DIR}/shell)
add_library(SH_UTIL STATIC lexer.yy.cc parser.tab.cc driver.cpp)
target_link_libraries(SH_UTIL formula)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare")
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-null-conversion -Wno-unneeded-internal-declaration -Wno-deprecated-register")
endif ()
