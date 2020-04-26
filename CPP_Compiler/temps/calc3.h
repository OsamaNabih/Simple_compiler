typedef enum { typeCon, typeId, typeOpr } nodeEnum;
typedef enum { intType, doubleType } typeEnum;

#include <unordered_map>

/* constants */
typedef struct {
	typeEnum type;				/* 0: int, 1: double */
	union {
		int iValue;             /* integer value */
		double dValue;			/* double value  */
	};
} conNodeType;

/* identifiers */
typedef struct {
    int i;                      /* subscript to sym array */
} idNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
	int temp_id;
	conNodeType value;
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

class SymTable {
	
	
};

extern double sym[26];
