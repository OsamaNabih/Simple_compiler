/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    VARIABLE = 259,
    DOUBLE = 260,
    INT_TYPE = 261,
    DOUBLE_TYPE = 262,
    CHAR_TYPE = 263,
    STRING_TYPE = 264,
    WHILE = 265,
    FOR = 266,
    IF = 267,
    PRINT = 268,
    SWITCH = 269,
    CASE = 270,
    DEFAULT = 271,
    BREAK = 272,
    AND = 273,
    OR = 274,
    NOT = 275,
    BIT_OR = 276,
    BIT_AND = 277,
    BIT_XOR = 278,
    BIT_NOT = 279,
    L_SHIFT = 280,
    R_SHIFT = 281,
    INC = 282,
    DEC = 283,
    POST_INC = 284,
    POST_DEC = 285,
    PRE_INC = 286,
    PRE_DEC = 287,
    IFX = 288,
    ELSE = 289,
    POST = 290,
    GE = 291,
    LE = 292,
    EQ = 293,
    NE = 294,
    UMINUS = 295
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define VARIABLE 259
#define DOUBLE 260
#define INT_TYPE 261
#define DOUBLE_TYPE 262
#define CHAR_TYPE 263
#define STRING_TYPE 264
#define WHILE 265
#define FOR 266
#define IF 267
#define PRINT 268
#define SWITCH 269
#define CASE 270
#define DEFAULT 271
#define BREAK 272
#define AND 273
#define OR 274
#define NOT 275
#define BIT_OR 276
#define BIT_AND 277
#define BIT_XOR 278
#define BIT_NOT 279
#define L_SHIFT 280
#define R_SHIFT 281
#define INC 282
#define DEC 283
#define POST_INC 284
#define POST_DEC 285
#define PRE_INC 286
#define PRE_DEC 287
#define IFX 288
#define ELSE 289
#define POST 290
#define GE 291
#define LE 292
#define EQ 293
#define NE 294
#define UMINUS 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "grammar.y" /* yacc.c:1909  */

    int iValue;                 /* integer value */
	double dValue;				/* double value  */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */

#line 141 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
