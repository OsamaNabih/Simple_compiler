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
    WHILE = 261,
    IF = 262,
    PRINT = 263,
    SWITCH = 264,
    CASE = 265,
    DEFAULT = 266,
    BREAK = 267,
    AND = 268,
    OR = 269,
    NOT = 270,
    BIT_OR = 271,
    BIT_AND = 272,
    BIT_XOR = 273,
    BIT_NOT = 274,
    L_SHIFT = 275,
    R_SHIFT = 276,
    IFX = 277,
    ELSE = 278,
    GE = 279,
    LE = 280,
    EQ = 281,
    NE = 282,
    UMINUS = 283
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define VARIABLE 259
#define DOUBLE 260
#define WHILE 261
#define IF 262
#define PRINT 263
#define SWITCH 264
#define CASE 265
#define DEFAULT 266
#define BREAK 267
#define AND 268
#define OR 269
#define NOT 270
#define BIT_OR 271
#define BIT_AND 272
#define BIT_XOR 273
#define BIT_NOT 274
#define L_SHIFT 275
#define R_SHIFT 276
#define IFX 277
#define ELSE 278
#define GE 279
#define LE 280
#define EQ 281
#define NE 282
#define UMINUS 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "grammar.y" /* yacc.c:1909  */

    int iValue;                 /* integer value */
	double dValue;				/* double value  */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */

#line 117 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
