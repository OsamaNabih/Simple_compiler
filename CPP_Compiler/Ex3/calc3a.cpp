#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

void printValue(nodeType* p);
void printQuad(nodeType* p);
double getValue(nodeType* p);

double ex(nodeType *p) {
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       { if (p->con.type == intType) return p->con.iValue; return p->con.dValue; }
    case typeId:        return sym[p->id.i];
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:     while(ex(p->opr.op[0])) ex(p->opr.op[1]); return 0;
        case IF:        if (ex(p->opr.op[0]))
                            ex(p->opr.op[1]);
                        else if (p->opr.nops > 2)
                            ex(p->opr.op[2]);
                        return 0;
        case PRINT:     printf("%d\n", ex(p->opr.op[0])); return 0;
        case ';':       ex(p->opr.op[0]); return ex(p->opr.op[1]);
        case '=':       {
							sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
							printf("%c = ", (char)p->opr.op[0]->id.i + 'a');
							printQuad(p->opr.op[1]);
							printf("\n");
							return sym[p->opr.op[0]->id.i];
						}
        case UMINUS:    {
							printf("t%d = ", p->opr.temp_id);
							printQuad(p->opr.op[0]);
							return -ex(p->opr.op[0]);
						}
        case '+':       { 
							double left = ex(p->opr.op[0]);
							double right = ex(p->opr.op[1]);
							printf("t%d = ", p->opr.temp_id);
							printQuad(p->opr.op[0]);
							printf("+");
							printQuad(p->opr.op[1]);
							printf("\n");
							return left + right;
						}
        case '-':       { 
							double left = ex(p->opr.op[0]);
							double right = ex(p->opr.op[1]);
							printf("t%d = ", p->opr.temp_id);
							printQuad(p->opr.op[0]);
							printf("-");
							printQuad(p->opr.op[1]);
							printf("\n");
							return left - right;
						}
        case '*':       { 
							double left = ex(p->opr.op[0]);
							double right = ex(p->opr.op[1]);
							printf("t%d = ", p->opr.temp_id);
							printQuad(p->opr.op[0]);
							printf("*");
							printQuad(p->opr.op[1]);
							printf("\n");
							return left * right;
						}
        case '/':       { 
							double left = ex(p->opr.op[0]);
							double right = ex(p->opr.op[1]);
							printf("t%d = ", p->opr.temp_id);
							printQuad(p->opr.op[0]);
							printf("/");
							printQuad(p->opr.op[1]);
							printf("\n");
							return left / right;
						}
        case '<':       return ex(p->opr.op[0]) < ex(p->opr.op[1]);
        case '>':       return ex(p->opr.op[0]) > ex(p->opr.op[1]);
        case GE:        return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
        case LE:        return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
        case NE:        return ex(p->opr.op[0]) != ex(p->opr.op[1]);
        case EQ:        return ex(p->opr.op[0]) == ex(p->opr.op[1]);
        }
    }
    return 0;
}


void printValue(nodeType* p) {
	conNodeType con;
	if (p->type == typeOpr)
		con = p->opr.value;
	else 
		con = p->con;
	if (con.type == intType)
		printf(" %d ", con.iValue);
	else
		printf(" %f ", con.dValue);
}

void printQuad(nodeType* p) {
	if (p->type == typeCon)
		printValue(p);
	else if (p->type == typeOpr)
		printf(" t%d ", p->opr.temp_id);
}

double getValue(nodeType* p) {
	conNodeType con;
	if (p->type == typeOpr)
		con = p->opr.value;
	else 
		con = p->con;
	if (con.type == intType)
		return con.iValue;
	else
		return con.dValue;
}