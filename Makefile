# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -g
BISON = bison
FLEX = flex

SOURCES = main.c ast.c dgml_writer.c parser_interface.c
HEADERS = ast.h dgml_writer.h parser_interface.h
PARSER_SOURCES = parser.tab.c lex.yy.c

all: lab1

lab1: $(SOURCES) $(PARSER_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(PARSER_SOURCES)

parser.tab.c parser.tab.h: parser.y
	$(BISON) -d parser.y

lex.yy.c: lexer.l parser.tab.h
	$(FLEX) lexer.l

clean:
	rm -f lab1 parser.tab.c parser.tab.h lex.yy.c *.dgml

test: lab1
	./lab1 test.txt -o test_output.dgml

.PHONY: all clean test