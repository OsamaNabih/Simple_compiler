%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calc3.h"

/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(int i);
nodeType *intCon(int iValue);
nodeType *doubleCon(double dValue);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);

void yyerror(char *s);
int sym[26];                    /* symbol table */
%}

%union {
    int iValue;                 /* integer value */
	double dValue;				/* double value  */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token <dValue> DOUBLE
%token WHILE IF PRINT SWITCH CASE DEFAULT BREAK 
%token AND OR NOT 
%token BIT_OR BIT_AND BIT_XOR BIT_NOT L_SHIFT R_SHIFT 
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<' AND OR NOT
%left BIT_OR BIT_AND BIT_XOR BIT_NOT L_SHIFT R_SHIFT
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list case_stmt default_stmt case_stmt_list switch_body

%%

program:
        function                { exit(0); }
        ;

function:
          function stmt         { ex($2); freeNode($2); }
        | %empty
        ;

stmt:
          ';'                            { $$ = opr(';', 2, NULL, NULL); }
        | expr ';'                       { $$ = $1; }
        | PRINT expr ';'                 { $$ = opr(PRINT, 1, $2); }
        | VARIABLE '=' expr ';'          { $$ = opr('=', 2, id($1), $3); }
        | WHILE '(' expr ')' stmt        { $$ = opr(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
		| SWITCH '(' expr ')' '{' switch_body '}' { $$ = opr(SWITCH, 2, $3, $6); }
        | '{' stmt_list '}'              { $$ = $2; }
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

case_stmt:
		  CASE '(' expr ')' ':' stmt_list BREAK ';'	{ $$ = opr(CASE, 2, $3, $6); }
		;

default_stmt:
		  DEFAULT ':' stmt_list	BREAK ';'		{ $$ = opr(DEFAULT, 1, $3); }
		;

case_stmt_list:
		  case_stmt								{ $$ = opr('_', 1, $1); }
		| case_stmt_list case_stmt   			{ $$ = opr('#', 2, $1, $2); }

switch_body:
		  case_stmt_list						{ $$ = opr('!', 1, $1); }
		| case_stmt_list default_stmt			{ $$ = opr('#', 2, $1, $2); }

/*
case_stmt_list:
		  case_stmt								{ $$ = opr(';', 1, $1); }
		| case_stmt_no_def_list default_stmt 	{ $$ = opr(';', 2, $1, $2); }
		| case_stmt_list case_stmt   			{ $$ = opr(';', 2, $1, $2); }
		
case_stmt_no_def_list:
		  case_stmt case_stmt_no_def_list  		{ $$ = opr(';', 2, $1, $2); }
		;
*/

expr:
          INTEGER               { $$ = intCon($1); }
		| DOUBLE				{ $$ = doubleCon($1); }
        | VARIABLE              { $$ = id($1); }
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
		| expr AND expr			{ $$ = opr(AND, 2, $1, $3); }
		| expr OR expr			{ $$ = opr(OR, 2, $1, $3); }
		| NOT expr				{ $$ = opr(NOT, 1, $2); }
		| expr BIT_AND expr		{ $$ = opr(BIT_AND, 2, $1, $3); }
		| expr BIT_OR expr		{ $$ = opr(BIT_OR, 2, $1, $3); }
		| expr BIT_XOR expr		{ $$ = opr(BIT_XOR, 2, $1, $3); }
		| BIT_NOT expr			{ $$ = opr(BIT_NOT, 1, $2); }
		| expr L_SHIFT expr		{ $$ = opr(L_SHIFT, 2, $1, $3); }
		| expr R_SHIFT expr		{ $$ = opr(R_SHIFT, 2, $1, $3); }
        ;

%%

nodeType *intCon(int iValue) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
	p->type = typeIntCon;
	p->con.iValue = iValue;
    return p;
}

nodeType *doubleCon(double dValue) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
	p->type = typeDoubleCon;
	p->con.dValue = dValue;
    return p;
}

nodeType *id(int i) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    p->id.i = i;

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    /* allocate node, extending op array */
    if ((p = malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
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
