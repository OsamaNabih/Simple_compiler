%{
#include <stdlib.h>
#include "calc3.h"
#include "y.tab.h"
void yyerror(char *);
%}

%%

"int"			return INT_TYPE;
"double"		return DOUBLE_TYPE;
"char"			return CHAR_TYPE;
"string"		return STRING_TYPE;

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"while"         return WHILE;
"for"			return FOR;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;
"switch"		return SWITCH;
"case"			return CASE;
"default"		return DEFAULT;
"break"			return BREAK;
"&&"			return AND;
"||"			return OR;
"!"				return NOT;
"|"				return BIT_OR;
"&"				return BIT_AND;
"^"				return BIT_XOR;
"~"				return BIT_NOT;
"<<"			return L_SHIFT;
">>"			return R_SHIFT;
"++"			return INC;
"--"			return DEC;

[a-z]       { 
                yylval.sIndex = *yytext - 'a';
                return VARIABLE;
            }
			
0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[1-9][0-9]* {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }
			

[0-9]+(\.[0-9]+)?([eE][-+]?[0-9]+)?		{
											yylval.dValue = atof(yytext);
											return DOUBLE;
										}

[-()<>=+*/;{}.:] {
                return *yytext;
             }



[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");
%%
int yywrap(void) {
    return 1;
}
