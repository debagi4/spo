#include "../parser/grammar/BagiLexer.h"
#include "../parser/grammar/BagiParser.h"
#include "../parser/grammar/BagiBaseListener.h"
#include "antlr4-runtime.h"
#include "Tree.h"
#include "parse_wrapper.h"
#include <string>

using namespace antlr4;

// Слушатель для построения AST
class TreeListener : public BagiBaseListener {
public:
    Tree* tree;
    std::vector<Tree*> stack;  // стек родителей
    std::vector<Tree*> all_nodes;
    std::vector<char*> errors;

    TreeListener() {
        tree = create_node("root", "");
        stack.push_back(tree);
        all_nodes.push_back(tree);
    }

    // Вспомогательная функция для добавления узла к текущему родителю
    void add_node(Tree* node) {
        Tree* parent = stack.back();
        add_child(parent, node);
        stack.push_back(node); // новый узел становится текущим родителем
        all_nodes.push_back(node);
    }

    void add_error(const std::string& error) {
        errors.push_back(strdup(error.c_str()));
    }

    // После выхода из узла убираем его из стека
    void pop_node() {
        stack.pop_back();
    }

    void enterFuncDef(BagiParser::FuncDefContext *ctx) override {
        Tree* node = create_node("funcDef", ctx->getText().c_str());
        add_node(node);
    }
    void exitFuncDef(BagiParser::FuncDefContext *ctx) override {
        pop_node();
    }

    void enterBlock(BagiParser::BlockContext *ctx) override {
        Tree* node = create_node("block", ctx->getText().c_str());
        add_node(node);
    }
    void exitBlock(BagiParser::BlockContext *ctx) override {
        pop_node();
    }

    void enterVarDecl(BagiParser::VarDeclContext *ctx) override {
        Tree* node = create_node("varDecl", ctx->getText().c_str());
        add_node(node);
        pop_node(); // varDecl не имеет детей
    }

    void enterExprStatement(BagiParser::ExprStatementContext *ctx) override {
        Tree* node = create_node("expr", ctx->getText().c_str());
        add_node(node);
        pop_node(); // expr не имеет детей
    }

    void enterIfStatement(BagiParser::IfStatementContext *ctx) override {
        Tree* node = create_node("if", ctx->getText().c_str());
        add_node(node);
    }
    void exitIfStatement(BagiParser::IfStatementContext *ctx) override {
        pop_node();
    }

    void enterWhileStatement(BagiParser::WhileStatementContext *ctx) override {
        Tree* node = create_node("while", ctx->getText().c_str());
        add_node(node);
    }
    void exitWhileStatement(BagiParser::WhileStatementContext *ctx) override {
        pop_node();
    }

    void enterDoWhileStatement(BagiParser::DoWhileStatementContext *ctx) override {
        Tree* node = create_node("doWhile", ctx->getText().c_str());
        add_node(node);
    }
    void exitDoWhileStatement(BagiParser::DoWhileStatementContext *ctx) override {
        pop_node();
    }
};

extern "C" {
    ParseResult* parse(const char* inp) {
        ANTLRInputStream input(inp);
        BagiLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        BagiParser parser(&tokens);

        antlr4::tree::ParseTree* parse_tree = parser.source();  // корень

        TreeListener listener;
        antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, parse_tree);

        ParseResult* result = new ParseResult();
        result->size = listener.all_nodes.size();
        result->tree = listener.tree;

        result->nodes = new Tree*[listener.all_nodes.size()];
        for (size_t i = 0; i < listener.all_nodes.size(); ++i) {
            result->nodes[i] = listener.all_nodes[i];
        }

        result->errors = new char*[listener.errors.size()];
        for (size_t i = 0; i < listener.errors.size(); ++i) {
            result->errors[i] = listener.errors[i];
        }
        result->errorsCount = listener.errors.size();

        return result;
    }
}
