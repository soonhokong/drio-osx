CC    ?= clang
CXX   ?= clang++

EXE = shell

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++11

CFLAGS = -O0  $(CDEBUG) $(CSTD) 
CXXFLAGS = -O0  $(CXXDEBUG) $(CXXSTD)

CPPOBJ = main sh_driver scoped_env
SOBJ =  parser lexer

FILES = $(addsuffix .cpp, $(CPPOBJ))

OBJS  = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
			 sh_parser.tab.cc sh_parser.tab.hh \
				 location.hh position.hh \
			    stack.hh sh_parser.output parser.o \
				 lexer.o sh_lexer.yy.cc $(EXE)\

.PHONY: all
all: shell

shell: 	$(FILES)
		$(MAKE) $(SOBJ)
		$(MAKE) $(OBJS)
		$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)

parser: sh_parser.yy
	/usr/local/opt/bison/bin/bison -d -v sh_parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o sh_parser.tab.cc

lexer: sh_scanner.l
	flex --outfile=sh_lexer.yy.cc   $<
	$(CXX)  $(CXXFLAGS) -c sh_lexer.yy.cc -o lexer.o -Wno-deprecated-register

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)
	