#Custon command for flex/bison

ADD_CUSTOM_COMMAND(
	OUTPUT	(${DRIO_BINARY_DIR}/shell/parser.tab.cc
			 ${DRIO_BINARY_DIR}/shell/parser.tab.hh)
	COMMAND	${BISON_EXECUTABLE}
	ARGS -d -v ${DRIO_SOURCE_DIR}/shell/parser.yy 
	)

ADD_CUSTOM_COMMAND(
        OUTPUT ${DRIO_BINARY_DIR}/shell/lexer.yy.cc
        COMMAND ${FLEX_EXECUTABLE}
        ARGS --outfile=${DRIO_BINARY_DIR}/shell/lexer.yy.cc ${DRIO_SOURCE_DIR}/shell/scanner.l
        DEPENDS ${DRIO_BINARY_DIR}/shell/parser.tab.hh
        )


SET_SOURCE_FILES_PROPERTIES(${DRIO_BINARY_DIR}/shell/lexer.yy.cc GENERATED)
SET_SOURCE_FILES_PROPERTIES(${DRIO_BINARY_DIR}/shell/parser.tab.cc GENERATED)

INCLUDE_DIRECTORIES(${DRIO_BINARY_DIR}/shell)
add_library(SH_UTIL STATIC lexer.yy.cc parser.tab.cc driver.cpp var_scoped_env.cpp fmla_scoped_env.cpp)
