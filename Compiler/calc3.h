typedef enum { typeIntCon, typeDoubleCon, typeId, typeOpr } nodeEnum;

/* constants */
typedef struct {
	int type;
	union {
		int iValue;                  /* value of integer constant */
		int dValue;					 /* value of double constant  */
	};
} conNodeType;

/* identifiers */
typedef struct {
	int type;					/* integer: 0, double: 1, char: 2, string: 3 */
	union {
		int ii;
		double d;
		char c;
		char* s;				/* implement strings as char* for now */
		/* string support to be added */
	};
    int i;                      /* subscript to sym array */
} idNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
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

extern int sym[26];
