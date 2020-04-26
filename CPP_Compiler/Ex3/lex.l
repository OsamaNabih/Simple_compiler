%{
#include <stdlib.h>
#include "calc3.h"
#include "y.tab.h"
void yyerror(char *);
#include <iostream>
using namespace std;
%}

%%

[ \r\t\n]+        ;       /* ignore whitespace */

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

[-()<>=+*/;{}.] {
                return *yytext;
             }

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;
"int"			return INT_TYPE;
"double"		return DOUBLE_TYPE;
"char"			return CHAR_TYPE;
"string"		return STR_TYPE;


.               {
					yyerror("Unknown character");
					cout << *yytext << endl;
				}
%%
int yywrap(void) {
    return 1;
}
