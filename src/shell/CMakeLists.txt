#Custon command for flex/bison

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
	DEPENDS ${DRIO_BINARY_DIR}/shell/sh_parser.tab.hh
	)


SET_SOURCE_FILES_PROPERTIES(${DRIO_BINARY_DIR}/shell/sh_lexer.yy.cc GENERATED)
SET_SOURCE_FILES_PROPERTIES(${DRIO_BINARY_DIR}/shell/sh_parser.tab.cc GENERATED)

INCLUDE_DIRECTORIES(${DRIO_BINARY_DIR}/shell)
add_library(SH_UTIL STATIC sh_lexer.yy.cc sh_parser.tab.cc sh_driver.cpp scoped_env.cpp)