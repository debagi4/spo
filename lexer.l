%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

digit      [0-9]
letter     [a-zA-Z_]
whitespace [ \t\r\n]

%%

"if"          { return IF; }
"else"        { return ELSE; }
"while"       { return WHILE; }
"do"          { return DO; }
"break"       { return BREAK; }

"bool"        { yylval.str = strdup(yytext); return BUILTIN_TYPE; }
"byte"        { yylval.str = strdup(yytext); return BUILTIN_TYPE; }
"int"         { yylval.str = strdup(yytext); return BUILTIN_TYPE; }
"uint"        { yylval.str = strdup(yytext); return BUILTIN_TYPE; }
"long"        { yylval.str = strdup(yytext); return BUILTIN_TYPE; }
"ulong"       { yylval.str = strdup(yytext); return BUILTIN_TYPE; }
"char"        { yylval.str = strdup(yytext); return BUILTIN_TYPE; }
"string"      { yylval.str = strdup(yytext); return BUILTIN_TYPE; }

{letter}({letter}|{digit})*   {
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

"true"        { yylval.str = strdup(yytext); return BOOL_LITERAL; }
"false"       { yylval.str = strdup(yytext); return BOOL_LITERAL; }

0[xX][0-9A-Fa-f]+             {
    yylval.num = strtoul(yytext, NULL, 16);
    return HEX_LITERAL;
}

0[bB][01]+                    {
    yylval.num = strtoul(yytext + 2, NULL, 2);
    return BITS_LITERAL;
}

{digit}+                      {
    yylval.num = strtoul(yytext, NULL, 10);
    return DEC_LITERAL;
}

\"([^\\\"]|\\.)*\"            {
    yylval.str = strdup(yytext);
    return STRING_LITERAL;
}

\'([^\\\']|\\.)*\'            {
    /* Упрощенная обработка char литералов */
    if (strlen(yytext) == 3 && yytext[1] != '\\') {
        yylval.num = yytext[1];
    } else if (strlen(yytext) == 4 && yytext[1] == '\\') {
        /* escape sequence */
        switch(yytext[2]) {
            case 'n': yylval.num = '\n'; break;
            case 't': yylval.num = '\t'; break;
            case '\\': yylval.num = '\\'; break;
            case '\'': yylval.num = '\''; break;
            default: yylval.num = yytext[2]; break;
        }
    } else {
        yylval.num = 0; /* fallback */
    }
    return CHAR_LITERAL;
}

{whitespace}+   { /* игнорируем пробелы */ }
"//".*          { /* игнорируем однострочные комментарии */ }
"/*"([^*]|[*][^/])*"*/" { /* игнорируем многострочные комментарии */ }

"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }
"=="            { return yytext[0]; }  /* временно как отдельный символ */
"!="            { return yytext[0]; }  /* временно как отдельный символ */
">"             { return yytext[0]; }
"<"             { return yytext[0]; }
">="            { return yytext[0]; }
"<="            { return yytext[0]; }

.               { return yytext[0]; }

%%

int yywrap(void) {
    return 1;
}