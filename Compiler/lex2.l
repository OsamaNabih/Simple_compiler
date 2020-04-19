%{
#include <stdlib.h>
#include "calc3.h"
#include "y.tab.h"
void yyerror(char *);
%}

%%

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

[-()<>=+*/;{}.:] {
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
"switch"		return SWITCH;
"case"			return CASE;
"default"		return DEFAULT;
"break"			return BREAK;
"&&"			return AND;
"||"			return OR;
"|"				return BIT_OR;
"&"				return BIT_AND;
"^"				return BIT_XOR;
"!"				return NOT;
"switch"		return SWITCH;
"case"			return CASE;
"break"			return BREAK;
"default"		return DEFAULT;

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");
%%
int yywrap(void) {
    return 1;
}
