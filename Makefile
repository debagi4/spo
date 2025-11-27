# Компиляторы
CXX = g++
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -g -I./src -I./parser/grammar -I/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/include/antlr4-runtime
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I./src -I./parser/grammar -I/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/include/antlr4-runtime

# Флаги линковки
LDFLAGS = -L/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/lib -lantlr4-runtime

# Исходники
SRC_C = src/main.c src/dgml_writer.c src/Tree.c src/cfg_from_tree.c src/cfg_builder.c src/dot_writer.c
SRC_CPP = src/parser_wrapper.cpp parser/grammar/BagiLexer.cpp parser/grammar/BagiParser.cpp parser/grammar/BagiBaseListener.cpp parser/grammar/BagiListener.cpp

# Объекты
OBJ_C = $(SRC_C:.c=.o)
OBJ_CPP = $(SRC_CPP:.cpp=.o)

# ANTLR
ANTLR_BIN = antlr-4.13.2-complete.jar
GRAMMAR = grammar/Bagi.g4
ANTLR_OUT = parser

# Цель по умолчанию
all: clean make_parser lab1 test

# Генерация парсера ANTLR
make_parser:
	java -jar $(ANTLR_BIN) -Dlanguage=Cpp -visitor -o $(ANTLR_OUT) $(GRAMMAR)

# Сборка программы
lab1: $(OBJ_C) $(OBJ_CPP)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Правила компиляции C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Правила компиляции C++
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: lab1
	./lab1 output test.txt

test2: lab1
	./lab1 output test2.txt

debug: lab1
	lldb ./lab1

# Очистка
clean:
	rm -f $(OBJ_C) $(OBJ_CPP) lab1
