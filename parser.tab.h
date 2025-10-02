/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     DEC_LITERAL = 259,
     HEX_LITERAL = 260,
     BITS_LITERAL = 261,
     STRING_LITERAL = 262,
     CHAR_LITERAL = 263,
     BOOL_LITERAL = 264,
     BUILTIN_TYPE = 265,
     IF = 266,
     ELSE = 267,
     WHILE = 268,
     DO = 269,
     BREAK = 270,
     OR = 271,
     AND = 272,
     NOT = 277
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define DEC_LITERAL 259
#define HEX_LITERAL 260
#define BITS_LITERAL 261
#define STRING_LITERAL 262
#define CHAR_LITERAL 263
#define BOOL_LITERAL 264
#define BUILTIN_TYPE 265
#define IF 266
#define ELSE 267
#define WHILE 268
#define DO 269
#define BREAK 270
#define OR 271
#define AND 272
#define NOT 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 26 "parser.y"
{
    char *str;
    unsigned long num;
    Node *node;
}
/* Line 1529 of yacc.c.  */
#line 91 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

