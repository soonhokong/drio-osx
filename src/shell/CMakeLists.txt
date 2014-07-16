#Custon command for flex/bison

ADD_CUSTOM_COMMAND(
        OUTPUT ${DRIO_BINARY_DIR}/shell/parser.tab.cc
        COMMAND ${BISON_EXECUTABLE}
        ARGS -d -v ${DRIO_SOURCE_DIR}/shell/parser.yy
        DEPENDS ${DRIO_SOURCE_DIR}/shell/parser.yy
        DEPENDS ${DRIO_SOURCE_DIR}/shell/scanner.l
        )

ADD_CUSTOM_COMMAND(
        OUTPUT ${DRIO_BINARY_DIR}/shell/lexer.yy.cc
        COMMAND ${FLEX_EXECUTABLE}
        ARGS --outfile=${DRIO_BINARY_DIR}/shell/lexer.yy.cc ${DRIO_SOURCE_DIR}/shell/scanner.l
        DEPENDS ${DRIO_SOURCE_DIR}/shell/scanner.l
        )

# Add parser.tab.cc to the list of sources
SET(DRIO_SRCS ${DRIO_SRCS} ${DRIO_BINARY_DIR}/shell/parser.tab.cc)
SET_SOURCE_FILES_PROPERTIES(${DRIO_BINARY_DIR}/shell/parser.tab.cc GENERATED)

INCLUDE_DIRECTORIES(${DRIO_BINARY_DIR}/shell)
add_library(SH_UTIL STATIC lexer.yy.cc parser.tab.cc driver.cpp var_scoped_env.cpp fmla_scoped_env.cpp)
