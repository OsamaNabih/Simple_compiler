%{
#include <stdlib.h>
#include "calc3.h"
#include "y.tab.h"
void yyerror(char *);
#include <iostream>
#include <typeinfo>
using namespace std;
%}

%%

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;
"int"			{ cout << "Found an int type\n"; return INT_TYPE; }
"double"		return DOUBLE_TYPE;
"char"			return CHAR_TYPE;
"string"		return STR_TYPE;
"//".*			;
"/*".*"*/"		;


[-()<>=+*/;{}.] {
				printf("Matched an operator %c\n", *yytext);
                return *yytext;
				}
				
0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[1-9][0-9]* {
				cout << "Matched an int: " << atoi(yytext) << endl;
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[_]?[a-zA-Z][_a-zA-Z0-9]*       { 
				cout << "Matched an identifier: " << yytext << endl;
				strcpy(yylval.sValue, yytext);
				//yylval.sValue[yytext-1] = '\0';
				//yylval.s = yytext;
				return VARIABLE;
            }
			
\".*\"		{
				cout << "Matched a string: " << yytext << endl;
				strncpy(yylval.sValue, &yytext[1], yyleng - 2);
				//yylval.sValue[yytext-1] = '\0';
				return STRING;
			}
			
[0-9]+(\.[0-9]+)?([eE][-+]?[0-9]+)?		{
											cout << "Matched a double: " << atof(yytext) << endl;
											yylval.dValue = atof(yytext);
											return DOUBLE;
										}

\'.\'	{
			cout << "Matched a char\n";
			yylval.cValue = *yytext;
			return CHAR;
		}

[ \r\t\n]+        ;       /* ignore whitespace */

.               {
					yyerror("Unknown character");
					cout << *yytext << endl;
				}
%%
int yywrap(void) {
    return 1;
}
