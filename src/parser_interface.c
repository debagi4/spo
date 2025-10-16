#include "parser_interface.h"
#include "Tree.h"
#include "./parser/grammar/BagiLexer.h"
#include "./parser/grammar/BagiParser.h"
#include "antlr4-runtime.h"
#include <stdlib.h>
#include <string.h>

// Вспомогательная функция для рекурсивного обхода parse tree
static Tree* build_ast(antlr4::tree::ParseTree* tree) {
    if(!tree) return NULL;

    const char* node_text = tree->getText().c_str();
    Tree* node = create_node(tree->getClassName().c_str(), node_text);

    size_t count = tree->getChildCount();
    for(size_t i=0; i<count; i++) {
        Tree* child = build_ast(tree->getChild(i));
        if(child) add_child(node, child);
    }
    return node;
}

Tree* parse_text(const char* text) {
    // Создаем поток символов
    ANTLRInputStream* input = ANTLRInputStreamNew(text, strlen(text));

    // Лексер
    BagiLexer* lexer = BagiLexerNew(input);
    CommonTokenStream* tokens = CommonTokenStreamNew((Lexer*)lexer);

    // Парсер
    BagiParser* parser = BagiParserNew(tokens);
    // Парсим корень
    antlr4::tree::ParseTree* tree = parser->source(parser);

    // Строим AST
    Tree* root = build_ast(tree);

    // Освобождаем ANTLR объекты
    CommonTokenStreamFree(tokens);
    BagiLexerFree(lexer);
    BagiParserFree(parser);
    ANTLRInputStreamFree(input);

    return root;
}