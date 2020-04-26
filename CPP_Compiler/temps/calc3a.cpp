#include <iostream>
#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"
#include <algorithm>
using namespace std;
void printValue(nodeType* p);
void printQuad(nodeType* p);
void setLeftId(nodeType* p);
void setRightId(nodeType* p);
void setId(nodeType* p);
void printIdentifier(nodeType* p);
void printIds(nodeType* p);

double ex(nodeType *p) {
    if (!p) return 0;
    switch(p->type) {
	case typeId:        return sym[p->id.i];
    case typeCon:       { if (p->con.type == intType) return p->con.iValue; return p->con.dValue; }
	case typeOpr:
		switch(p->opr.oper) {
			case '+':	 {	
							setLeftId(p);
							double left = ex(p->opr.op[0]);
							setRightId(p);
							double right = ex(p->opr.op[1]);
							setId(p);
							int my_id = p->opr.temp_id;
							//printf("Op1: %d, op2: %d, id: %d\n", (int)left, (int)right, my_id);
							printIds(p);
							//printf("Left id: %d, right id: %d, my id: %d\n", p->opr.op[0]->opr.temp_id, p->opr.op[1]->opr.temp_id, my_id);
							printf("t%d = ", my_id);
							printQuad(p->opr.op[0]);
							printf("+");
							printQuad(p->opr.op[1]);
							printf("%d\n", left + right);
							printf("\n\n");
							return left + right;	
						}
			case '*':	{
							setLeftId(p);
							double left = ex(p->opr.op[0]);
							setRightId(p);
							double right = ex(p->opr.op[1]);
							setId(p);
							int my_id = p->opr.temp_id;
							//printf("Op1: %d, op2: %d, id: %d\n", (int)left, (int)right, my_id);
							//printf("Left id: %d, right id: %d, my id: %d\n", p->opr.op[0]->opr.temp_id, p->opr.op[1]->opr.temp_id, my_id);
							printIds(p);
							printf("t%d = ", my_id);
							printQuad(p->opr.op[0]);
							printf("*");
							printQuad(p->opr.op[1]);
							printf("%d\n", left * right);
							printf("\n\n");
							return left * right;	
						}
			case PRINT:    { printf("%d\n", ex(p->opr.op[0])); return 0; }
			case '=':       return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
			
		}
	}
	/*
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
        case '=':       return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
        case UMINUS:    return -ex(p->opr.op[0]);
        case '+':       return ex(p->opr.op[0]) + ex(p->opr.op[1]);
        case '-':       return ex(p->opr.op[0]) - ex(p->opr.op[1]);
        case '*':       return ex(p->opr.op[0]) * ex(p->opr.op[1]);
        case '/':       return ex(p->opr.op[0]) / ex(p->opr.op[1]);
        case '<':       return ex(p->opr.op[0]) < ex(p->opr.op[1]);
        case '>':       return ex(p->opr.op[0]) > ex(p->opr.op[1]);
        case GE:        return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
        case LE:        return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
        case NE:        return ex(p->opr.op[0]) != ex(p->opr.op[1]);
        case EQ:        return ex(p->opr.op[0]) == ex(p->opr.op[1]);
        }
    }
	*/
    return 0;
}

void printIdentifier(nodeType* p) {
	
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

void setLeftId(nodeType* p) {
	if (p->opr.op[0]->type == typeOpr) { //If left operand is expression
		if (p->opr.temp_id != -1) { //Intermediate node in an expr	
			p->opr.op[0]->opr.temp_id = p->opr.temp_id;
			printf("Intermediate node\n");
		}
		else {
			p->opr.temp_id = 0;
			printf("New expression\n");
		}
			
	}
}

void setRightId(nodeType* p) {
	if (p->opr.op[0]->type == typeOpr)
		p->opr.temp_id = p->opr.op[0]->opr.temp_id + 1;
	if (p->opr.op[1]->type == typeOpr) {
		p->opr.op[1]->opr.temp_id = p->opr.temp_id;
	}
}

void setId(nodeType* p) {
	if (p->opr.op[1]->type == typeOpr)
		p->opr.temp_id = p->opr.op[1]->opr.temp_id + 1;
}

void printIds(nodeType* p) {
	if (p->opr.op[0]->type == typeOpr)
		printf("Left id: %d", p->opr.op[0]->opr.temp_id);
	if (p->opr.op[1]->type == typeOpr)
		printf("Right id: %d", p->opr.op[1]->opr.temp_id);
	if (p->opr.op[0]->type == typeOpr || p->opr.op[1]->type == typeOpr)
		printf("\n");
}