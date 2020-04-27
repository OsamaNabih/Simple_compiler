#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

typedef enum { typeCon, typeId, typeOpr } nodeEnum;
enum { intType, doubleType, charType, strType } typeEnum;

/* constants */
typedef struct {
    	int type;				/* 0: int, 1: double */
	union {
		int iValue;             /* integer value */
		double dValue;			/* double value  */
		char cValue;
		char sValue[100];
	};
} conNodeType;

/* identifiers */
struct idNodeType {                      
	char name[100];				/* subscript to sym array */
	int type;
};

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
	int temp_id;
	conNodeType con;
    struct nodeTypeTag *op[1];	/* operands, extended at runtime */
} oprNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    union {
        conNodeType con;        /* constants */
        idNodeType id;          /* identifiers */
        oprNodeType opr;        /* operators */
    };
} nodeType;

struct SymTable;

struct TableEntry {
	string name;
	conNodeType con;
	SymTable* scope = NULL;
};



extern unordered_map<string, TableEntry> sym;
extern vector<string> types {"int", "double", "char", "string"};

//extern int sym[26];
