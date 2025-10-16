grammar Bagi;

options {
  language = Cpp;
}

@header {
#include <string>
#include <vector>
}

IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
STRING: '"' (~["\\] | '\\' .)* '"';
CHAR: '\'' ~['\\] '\'';
HEX: '0' [xX] [0-9A-Fa-f]+;
BITS: '0' [bB] [01]+;
DEC: [0-9]+;
BOOL: 'true' | 'false';

WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
MULTICOMMENT: '/*' .*? '*/' -> skip;

// -------------------- Source --------------------
source: sourceItem* ;

sourceItem
    : funcDef
    ;

// -------------------- Functions --------------------
funcDef
    : funcSignature (block | ';')
    ;

funcSignature
    : typeRef? IDENTIFIER '(' argDefList? ')'
    ;

argDefList
    : argDef (',' argDef)*
    ;

argDef
    : typeRef? IDENTIFIER
    ;

// -------------------- Types --------------------
typeRef
    : baseType arraySuffix*
    ;

baseType
    : builtinType
    | customType
    ;

builtinType
    : 'bool' | 'byte' | 'int' | 'uint' | 'long' | 'ulong' | 'char' | 'string'
    ;

customType
    : IDENTIFIER
    ;

arraySuffix
    : '[' ']'
    ;

// -------------------- Statements --------------------
statement
    : varDecl
    | ifStatement
    | block
    | whileStatement
    | doWhileStatement
    | breakStatement
    | continueStatement
    | exprStatement
    ;

varDecl
    : typeRef? IDENTIFIER ('=' expr)? (',' IDENTIFIER ('=' expr)?)* ';'
    ;

varList
    : varItem (',' varItem)*
    ;

varItem
    : IDENTIFIER ('=' expr)?
    ;

ifStatement
    : 'if' '(' expr ')' statement ('else' statement)?
    ;

block
    : '{' statement* '}'
    ;

whileStatement
    : 'while' '(' expr ')' statement
    ;

doWhileStatement
    : 'do' block 'while' '(' expr ')' ';'
    ;

breakStatement
    : 'break' ';'
    ;

continueStatement
    : 'continue' ';'
    ;

exprStatement
    : expr ';'
    ;

// -------------------- Expressions --------------------
expr
    : expr '||' expr               # orExpr
    | expr '&&' expr               # andExpr
    | expr '|' expr                # bitOrExpr
    | expr '^' expr                # bitXorExpr
    | expr '&' expr                # bitAndExpr
    | expr ('==' | '!=') expr      # eqExpr
    | expr ('<' | '<=' | '>' | '>=') expr # cmpExpr
    | expr ('<<' | '>>') expr      # shiftExpr
    | expr ('+' | '-') expr        # addSubExpr
    | expr ('*' | '/' | '%') expr  # mulDivExpr
    | IDENTIFIER assignOp expr     # assignExpr
    | unOp expr                    # unaryExpr
    | '(' expr ')'                 # parensExpr
    | expr '(' exprList? ')'       # callExpr
    | expr '[' exprList? ']'       # indexerExpr
    | IDENTIFIER                   # placeExpr
    | literal                      # literalExpr
    ;

assignOp
    : '=' | '+=' | '-=' | '*=' | '/=' | '%='
    ;

unOp
    : '+' | '-' | '!' | '~'
    ;

exprList
    : expr (',' expr)*
    ;

literal
    : BOOL
    | STRING
    | CHAR
    | HEX
    | BITS
    | DEC
    ;
