#Custon command for flex/lex

ADD_CUSTOM_COMMAND(
	OUTPUT	(${DRIO_BINARY_DIR}/shell/sh_parser.tab.cc
			 ${DRIO_BINARY_DIR}/shell/sh_parser.tab.hh)
	COMMAND	/usr/local/opt/bison/bin/bison
	ARGS -d -v ${DRIO_SOURCE_DIR}/shell/sh_parser.yy
	)

ADD_CUSTOM_COMMAND(
	OUTPUT ${DRIO_BINARY_DIR}/shell/sh_lexer.yy.cc
	COMMAND ${FLEX_EXECUTABLE}
	ARGS --outfile=${DRIO_BINARY_DIR}/shell/sh_lexer.yy.cc ${DRIO_SOURCE_DIR}/shell/sh_scanner.l 
	)

SET_SOURCE_FILES_PROPERTIES(${DRIO_BINARY_DIR}/shell/sh_lexer.yy.cc GENERATED)
SET_SOURCE_FILES_PROPERTIES(${DRIO_BINARY_DIR}/shell/sh_parser.tab.cc GENERATED)

INCLUDE_DIRECTORIES(${DRIO_BINARY_DIR}/shell)
add_library(SH_UTIL sh_lexer.yy.cc sh_parser.tab.cc)

target_link_libraries(SH_UTIL SH_LIBS)