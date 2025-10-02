%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex(void);
extern FILE *yyin;

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

/* Глобальная переменная для корня AST */
Node *ast_root = NULL;
%}

%union {
    char *str;
    unsigned long num;
    Node *node;
}

%token <str> IDENTIFIER
%token <num> DEC_LITERAL HEX_LITERAL BITS_LITERAL
%token <str> STRING_LITERAL
%token <num> CHAR_LITERAL
%token <str> BOOL_LITERAL
%token <str> BUILTIN_TYPE

%token IF ELSE WHILE DO BREAK
%left OR
%left AND
%left '>' '<' '=' "==" "!=" ">=" "<="
%left '+' '-'
%left '*' '/'
%right NOT

%type <node> program
%type <node> source sourceItem
%type <node> funcDef argList argDef
%type <node> typeRef
%type <node> statement varDecl varList
%type <node> ifStmt whileStmt doWhileStmt breakStmt
%type <node> expr
%type <node> block statements

%%

program:
    source { ast_root = $1; $$ = $1; }
    ;

source:
    /* empty */ { $$ = node_new("program", NULL); }
    | source sourceItem {
        if ($1 == NULL) {
            $$ = node_new("program", NULL);
        } else {
            $$ = $1;
        }
        node_add_child($$, $2);
    }
    ;

sourceItem:
    funcDef ';' { $$ = $1; }
    | funcDef block {
        $$ = node_new("func_with_body", NULL);
        node_add_child($$, $1);
        node_add_child($$, $2);
    }
    ;

funcDef:
    typeRef IDENTIFIER '(' argList ')' {
        $$ = node_new("function", $2);
        node_add_child($$, $1);
        if ($4) node_add_child($$, $4);
    }
    ;

argList:
    /* empty */ { $$ = NULL; }
    | argDef { $$ = node_new("parameters", NULL); node_add_child($$, $1); }
    | argList ',' argDef {
        if ($1 == NULL) {
            $$ = node_new("parameters", NULL);
        } else {
            $$ = $1;
        }
        node_add_child($$, $3);
    }
    ;

argDef:
    typeRef IDENTIFIER {
        $$ = node_new("parameter", $2);
        node_add_child($$, $1);
    }
    ;

typeRef:
    BUILTIN_TYPE { $$ = node_new("type", $1); }
    | IDENTIFIER { $$ = node_new("type", $1); }
    | typeRef '[' ']' {
        $$ = node_new("array_type", NULL);
        node_add_child($$, $1);
    }
    ;

statement:
    varDecl { $$ = $1; }
    | ifStmt { $$ = $1; }
    | whileStmt { $$ = $1; }
    | doWhileStmt { $$ = $1; }
    | breakStmt { $$ = $1; }
    | expr ';' { $$ = node_new("expression_statement", NULL); node_add_child($$, $1); }
    | block { $$ = $1; }
    ;

block:
    '{' statements '}' { $$ = $2; }
    ;

statements:
    /* empty */ { $$ = node_new("block", NULL); }
    | statements statement {
        if ($1 == NULL) {
            $$ = node_new("block", NULL);
        } else {
            $$ = $1;
        }
        node_add_child($$, $2);
    }
    ;

varDecl:
    typeRef varList ';' {
        $$ = node_new("variable_declaration", NULL);
        node_add_child($$, $1);
        node_add_child($$, $2);
    }
    ;

varList:
    IDENTIFIER { $$ = node_new("variable", $1); }
    | varList ',' IDENTIFIER {
        if ($1 == NULL) {
            $$ = node_new("variable_list", NULL);
        } else {
            $$ = $1;
        }
        Node *var = node_new("variable", $3);
        node_add_child($$, var);
    }
    | varList ',' IDENTIFIER '=' expr {
        if ($1 == NULL) {
            $$ = node_new("variable_list", NULL);
        } else {
            $$ = $1;
        }
        Node *var = node_new("initialized_variable", $3);
        node_add_child(var, $5);
        node_add_child($$, var);
    }
    ;

ifStmt:
    IF '(' expr ')' statement {
        $$ = node_new("if", NULL);
        node_add_child($$, $3);
        node_add_child($$, $5);
    }
    | IF '(' expr ')' statement ELSE statement {
        $$ = node_new("if_else", NULL);
        node_add_child($$, $3);
        node_add_child($$, $5);
        node_add_child($$, $7);
    }
    ;

whileStmt:
    WHILE '(' expr ')' statement {
        $$ = node_new("while", NULL);
        node_add_child($$, $3);
        node_add_child($$, $5);
    }
    ;

doWhileStmt:
    DO block WHILE '(' expr ')' ';' {
        $$ = node_new("do_while", NULL);
        node_add_child($$, $2);
        node_add_child($$, $5);
    }
    ;

breakStmt:
    BREAK ';' { $$ = node_new("break", NULL); }
    ;

expr:
    expr '+' expr {
        $$ = node_new("binary_operator", "+");
        node_add_child($$, $1);
        node_add_child($$, $3);
    }
    | expr '-' expr {
        $$ = node_new("binary_operator", "-");
        node_add_child($$, $1);
        node_add_child($$, $3);
    }
    | expr '*' expr {
        $$ = node_new("binary_operator", "*");
        node_add_child($$, $1);
        node_add_child($$, $3);
    }
    | expr '/' expr {
        $$ = node_new("binary_operator", "/");
        node_add_child($$, $1);
        node_add_child($$, $3);
    }
    | expr '>' expr {
        $$ = node_new("binary_operator", ">");
        node_add_child($$, $1);
        node_add_child($$, $3);
    }
    | expr '<' expr {
        $$ = node_new("binary_operator", "<");
        node_add_child($$, $1);
        node_add_child($$, $3);
    }
    | expr '=' expr {
        $$ = node_new("assignment", "=");
        node_add_child($$, $1);
        node_add_child($$, $3);
    }
    | expr AND expr {
        $$ = node_new("binary_operator", "&&");
        node_add_child($$, $1);
        node_add_child($$, $3);
    }
    | expr OR expr {
        $$ = node_new("binary_operator", "||");
        node_add_child($$, $1);
        node_add_child($$, $3);
    }
    | '!' expr {
        $$ = node_new("unary_operator", "!");
        node_add_child($$, $2);
    }
    | '(' expr ')' { $$ = $2; }
    | IDENTIFIER '(' ')' {
        $$ = node_new("function_call", $1);
    }
    | IDENTIFIER '(' argList ')' {
        $$ = node_new("function_call", $1);
        if ($3) node_add_child($$, $3);
    }
    | IDENTIFIER '[' expr ']' {
        $$ = node_new("array_access", NULL);
        Node *id = node_new("identifier", $1);
        node_add_child($$, id);
        node_add_child($$, $3);
    }
    | IDENTIFIER { $$ = node_new("identifier", $1); }
    | STRING_LITERAL { $$ = node_new("string_literal", $1); }
    | CHAR_LITERAL {
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", (int)$1);
        $$ = node_new("char_literal", buf);
    }
    | DEC_LITERAL {
        char num[32];
        snprintf(num, sizeof(num), "%lu", $1);
        $$ = node_new("number_literal", num);
    }
    | HEX_LITERAL {
        char num[32];
        snprintf(num, sizeof(num), "0x%lX", $1);
        $$ = node_new("number_literal", num);
    }
    | BITS_LITERAL {
        char num[32];
        snprintf(num, sizeof(num), "0b%lu", $1);
        $$ = node_new("number_literal", num);
    }
    | BOOL_LITERAL { $$ = node_new("bool_literal", $1); }
    ;

%%

int parse_file(const char *fname, Node **root) {
    FILE *f = fopen(fname, "r");
    if (!f) { 
        perror("fopen"); 
        return 1; 
    }
    
    yyin = f;
    ast_root = NULL;
    
    int ret = yyparse();
    fclose(f);
    
    if (ret != 0) {
        return 1;
    }
    
    *root = ast_root;
    return 0;
}