#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"
#include <iostream>
using namespace std;

void printValue(nodeType* p);
void printQuad(nodeType* p);
double getValue(nodeType* p);
void printFromTable(nodeType* p);
void printTable();
int getType(nodeType* p);
int determineType(nodeType* p);

double ex(nodeType *p) {
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       { if (p->con.type == intType) return p->con.iValue; return p->con.dValue; }
    case typeId:        return sym[p->id.name].dVal;
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:     while(ex(p->opr.op[0])) ex(p->opr.op[1]); return 0;
        case IF:        if (ex(p->opr.op[0]))
                            ex(p->opr.op[1]);
                        else if (p->opr.nops > 2)
                            ex(p->opr.op[2]);
                        return 0;
        case PRINT:    printFromTable(p->opr.op[0]); return 0;
        case ';':       ex(p->opr.op[0]); return ex(p->opr.op[1]);
        case '=':       {
							//cout << "Are we here?\n";
							sym[p->opr.op[0]->id.name].iVal = ex(p->opr.op[1]);
							//cout << "Together we made it\n";
							sym[p->opr.op[0]->id.name].type = p->opr.op[1]->con.type;
							//cout << p->opr.op[1]->id.name << " = ";
							//printf("%c = ", (char)p->opr.op[0]->id.i + 'a');
							printQuad(p->opr.op[1]);
							printf("\n");
							cout << sym[p->opr.op[0]->id.name].iVal << endl;
							return sym[p->opr.op[0]->id.name].iVal;
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
		con = p->opr.con;
	else if (p->type == typeCon)
		con = p->con;
	else if (p->type == typeId)
		con = sym[p->id.name].con;
	if (con.type == intType)
		printf(" %d ", con.iValue);
	else if (con.type == doubleType)
		printf(" %f ", con.dValue);
	else if (con.type == charType)
		printf(" %c ", con.charValue;
	else if (con.type == strType)
		printf(" %s ", con.strValue;
}

void printQuad(nodeType* p) {
	if (p->type == typeCon)
		printValue(p);
	else if (p->type == typeOpr)
		printf(" t%d ", p->opr.temp_id);
	else if (p->type == typeId)
		cout << p->id.i;
}

double getValue(nodeType* p) {
	conNodeType con;
	if (p->type == typeOpr)
		con = p->opr.con;
	else if (p->type == typeCon)
		con = p->con;
	else if (p->type == typeId)
		con = sym[p->id.name].con;
	if (con.type == intType)
		return con.iValue;
	else
		return con.dValue;
}

void printFromTable(nodeType* p) {
	if (p->type == typeId) {
		cout << "Looking up value\n";
		if (sym.find(p->id.name) !=  sym.end()) printf("Symbol exists in table\n");
		else printf("No symbol matched\n");
		if (p->id.type == intType) {
			printf("Int type was found\n");
			printf("%d\n", sym[p->id.name].iVal);
			
		}
		else if (p->id.type == doubleType)
			printf("%f\n", sym[p->id.name].dVal);
		else if (p->id.type == charType)
			printf("%c\n", sym[p->id.name].cVal);
		else if (p->id.type == strType)
			printf("%s\n", sym[p->id.name].sVal);	
		}
	printTable();
}

void printTable() {
	for(auto kv : sym) {
		cout << kv.first << " ";
		cout << kv.second.iVal << " " << kv.second.type << endl;
	}		
	cout << endl;
}

int getType(nodeType* p) {
	if (p->type == typeOpr)
		return p->opr.con.type;
	else if (p->type == typeId) {
		if (sym.find(p->id.name) !=  sym.end())
			return sym[p->id.name].con.type;
		else {
			cout << "Variable: " << p->id.name << " hasn't been initialized\n";
			return -1;
		}
	}
	else if (p->type == typeCon)
		return p->con.type;
	return -1;
}

int determineType(nodeType* p) {
	int left_type = getType(p->opr.op[0]);
	int right_type = getType(p->opr.op[1]);
	if (left_type != right_type) {
		cout << "Type mismatch! Left op is type: " << types[left_type] << ", right op is type: " << types[right_type] << endl;
		throw("Type mismatch");
	}
	if ((left_type == intType && right_type == doubleType) || (right_type == intType && left_type == doubleType))
		cout << "Coercion bet. int and double\n";
}