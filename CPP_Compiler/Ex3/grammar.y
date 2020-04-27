%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calc3.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id_ass(string s);
nodeType *id_dec(int type, string s);
nodeType *intCon(int value);
nodeType *doubleCon(double value);
nodeType *charCon(char c);
nodeType *strCon(string s);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);

void yyerror(char *s);
unordered_map<string, TableEntry> sym;                    /* symbol table */

static int temp_id = 0;
%}

%union {
    int iValue;                 /* integer value */
	double dValue;
    nodeType *nPtr;             /* node pointer */
	char cValue;
	char sValue[100];
};

%token <iValue> INTEGER
%token <dValue> DOUBLE
%token <sValue> VARIABLE
%token <cValue> CHAR
%token <sValue> STRING

%token WHILE IF PRINT INT_TYPE DOUBLE_TYPE CHAR_TYPE STR_TYPE
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list
%type <iValue> dec_type 

%%

program:
        function                { exit(0); }
        ;

function:
          function stmt         { ex($2); freeNode($2); }
        | /* NULL */
        ;

stmt:
          ';'                            { $$ = opr(';', 2, NULL, NULL); temp_id = 0; }
        | expr ';'                       { $$ = $1; temp_id = 0; printf("\n"); }
        | PRINT expr ';'                 { $$ = opr(PRINT, 1, $2); temp_id = 0; }
        | VARIABLE '=' expr ';'          { $$ = opr('=', 2, id_ass($1), $3); temp_id = 0; printf("\n"); }
		| dec_type VARIABLE '=' expr ';' { printf("Parsed variable definition\n"); $$ = opr('=', 2, id_dec($1, $2), $4); temp_id = 0; printf("\n"); }
		| dec_type VARIABLE ';'    		 { $$ = id_dec($1, $2); temp_id = 0; }
        | WHILE '(' expr ')' stmt        { $$ = opr(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
        | '{' stmt_list '}'              { $$ = $2; }
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

expr:
          INTEGER               { printf("Parsed an int\n"); $$ = intCon($1); }
		| DOUBLE				{ $$ = doubleCon($1); }
		| CHAR					{ $$ = charCon($1);	}
		| STRING				{ $$ = strCon($1);	}
		| VARIABLE              { printf("Parsed a variable\n"); $$ = id_ass($1); }
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
        | expr '+' expr         { $$ = opr('+', 2, $1, $3); }
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); }
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); }
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); }
        | expr '<' expr         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); }
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); }
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); }
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }
        | '(' expr ')'          { $$ = $2; }
        ;

dec_type:
		  INT_TYPE				{ printf("Parsed an int type\n"); $$ = intType; }
		| DOUBLE_TYPE			{ $$ = doubleType; }
		| CHAR_TYPE				{ $$ = charType; }
		| STR_TYPE				{ $$ = strType; }

%%

nodeType *intCon(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
	p->con.type = intType;
    p->con.iValue = value;
	
    return p;
}

nodeType *doubleCon(double value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
	
    /* copy information */
    p->type = typeCon;
	p->con.type = doubleType;
    p->con.dValue = value;

    return p;
}

nodeType *charCon(char c) {
	nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
	
    /* copy information */
    p->type = typeCon;
	p->con.type = charType;
    p->con.cValue = c;

    return p;
}

nodeType* strCon(string s) {
	nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
	
    /* copy information */
    p->type = typeCon;
	p->con.type = strType;
	strcpy(p->con.sValue, s.c_str());

    return p;
}

nodeType *id_ass(string s) {
    nodeType *p;
    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
	
    /* copy information */
	p->type = typeId;
	p->id.type = -1;
	strcpy(p->id.name, s.c_str());
    return p;
}

nodeType *id_dec(int type, string s) {
    nodeType *p;
		
    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    strcpy(p->id.name, s.c_str());
	p->id.type = type;
    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    /* allocate node, extending op array */
    if ((p = (nodeType*)malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
	p->opr.temp_id = temp_id++;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    int i;
    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
