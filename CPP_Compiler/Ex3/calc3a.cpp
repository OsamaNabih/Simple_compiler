#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"
#include <iostream>
using namespace std;

void printValue(nodeType* p);
void printQuadOp(nodeType* p);
void printQuad(nodeType* p);
double getValue(nodeType* p);
void printFromTable(nodeType* p);
void printTable();
int getType(nodeType* p);
int determineType(nodeType* p);
double determineValue(nodeType* p, double left, double right);
vector<string> lang_types {"int", "double", "char", "string"};


double ex(nodeType *p) {
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       { if (p->con.type == intType) return p->con.iValue; return p->con.dValue; }
    case typeId:        { 
							if (sym[p->id.name].con.type == intType) return sym[p->id.name].con.iValue; 
							return sym[p->id.name].con.dValue; 
						}
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
							double right = ex(p->opr.op[1]);
							determineType(p);
							int type = p->opr.con.type = p->opr.op[0]->id.type;
							cout << "Determined type: " << type << "left type: " << p->opr.op[0]->id.type << endl;
							//TODO assign to proper field
							if (type == intType)
								sym[p->opr.op[0]->id.name].con.iValue = right;
							else if (type == doubleType)
								sym[p->opr.op[0]->id.name].con.dValue = right;
							sym[p->opr.op[0]->id.name].con.type = p->opr.op[0]->id.type;
							cout << p->opr.op[0]->id.name << " = ";
							//printf("%c = ", (char)p->opr.op[0]->id.i + 'a');
							printQuadOp(p->opr.op[1]);
							printf("\n");
							//cout << sym[p->opr.op[0]->id.name].con.iValue << endl;
							return sym[p->opr.op[0]->id.name].con.iValue;
						}
        case UMINUS:    {
							printf("t%d = ", p->opr.temp_id);
							printQuadOp(p->opr.op[0]);
							return -ex(p->opr.op[0]);
						}
        case '+':       
		case '-':
		case '*':
		case '/':		{
							double left = ex(p->opr.op[0]);
							double right = ex(p->opr.op[1]);
							//cout << "Type: " << lang_types[p->opr.con.type] << endl;
							p->opr.con.type = determineType(p);
							double result = determineValue(p, left, right);
							printQuad(p);
							return result;
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
		printf(" %c ", con.cValue);
	else if (con.type == strType)
		printf(" %s ", con.sValue);
}

void printQuadOp(nodeType* p) {
	if (p->type == typeCon)
		printValue(p);
	else if (p->type == typeOpr)
		printf(" t%d ", p->opr.temp_id);
	else if (p->type == typeId)
		printf(" %s ", p->id.name);
}

void printQuad(nodeType* p) {
	printf("t%d = ", p->opr.temp_id);
	printQuadOp(p->opr.op[0]);
	printf("%c", (char)p->opr.oper);
	printQuadOp(p->opr.op[1]);
	printf("\n");
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
			printf("%d\n", sym[p->id.name].con.iValue);
			
		}
		else if (p->id.type == doubleType)
			printf("%f\n", sym[p->id.name].con.dValue);
		else if (p->id.type == charType)
			printf("%c\n", sym[p->id.name].con.cValue);
		else if (p->id.type == strType)
			printf("%s\n", sym[p->id.name].con.sValue);	
		}
	printTable();
}

void printTable() {
	for(auto kv : sym) {
		cout << kv.first << " ";
		cout << kv.second.con.iValue << " " << kv.second.con.type << " " << kv.second.con.dValue << endl;
	}		
	cout << endl;
}

int getType(nodeType* p) {
	if (p->type == typeOpr) 
		return p->opr.con.type;
	else if (p->type == typeId) {
		if (sym.find(p->id.name) !=  sym.end())
			return sym[p->id.name].con.type;
		else if (p->id.type == -1) {
			cout << "Variable: " << p->id.name << " hasn't been initialized\n";
			throw "Variable: %s hasn't been initialized\n", p->id.name;
			cout << "Why am I here though2?\n";
			return -1;
		}
		else 
			return p->id.type; 
	}
	else if (p->type == typeCon)
		return p->con.type;
	cout << "About to return type -1\n";
	return -1;
}

int determineType(nodeType* p) {
	int left_type = getType(p->opr.op[0]);
	int right_type = getType(p->opr.op[1]);
	printf("Op: %c ltype:%d, rtype: %d\n", (char)p->opr.oper, left_type, right_type);
	if (left_type == right_type && (left_type == intType || left_type == doubleType))
		return p->opr.con.type = left_type;
	if ((left_type == intType && right_type == doubleType) || (right_type == intType && left_type == doubleType)) {
		if (left_type == intType && p->type == typeOpr && p->opr.oper == '=')
			printf("Assigning double to int, data loss due to truncation\n");
		else
			printf("Coercion from int to double\n");
		return p->opr.con.type = doubleType;
	}
	
	if (left_type != right_type) {
		cout << "Type mismatch! Left op is type: " << lang_types[left_type] << ", right op is type: " << lang_types[right_type] << endl;
		throw "Type mismatch";
	}
	if (p->opr.oper != '=' && (left_type == charType || left_type == strType || right_type == charType || right_type == strType))
		throw "Operation not defined for types %s %s", lang_types[left_type], lang_types[right_type];
	cout << "About to return type -1 in determine type\n";
	return p->opr.con.type = -1;
}


double determineValue(nodeType* p, double left, double right) {

	double result;
	switch(p->opr.oper) {
		case'+':	{ result = left + right; break; }
		case'-':	{ result = left - right; break; }
		case'*':	{ result = left * right; break; }
		case'/':	{ result = left / right; break; }
	}
	if (p->opr.con.type == intType)
		p->opr.con.iValue = result;
	else if (p->opr.con.type == doubleType)
		p->opr.con.dValue = result;
	return result;
}