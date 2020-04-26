#include <stdio.h>
#include <stdbool.h>
#include "calc3.h"
#include "y.tab.h"

void print_node(nodeType* node);

double ex(nodeType *p) {
    if (!p) return 0;
    switch(p->type) {
    case typeIntCon:       return p->con.iValue;
	case typeDoubleCon:    return p->con.dValue;
    case typeId:           return sym[p->id.i];
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:     while(ex(p->opr.op[0])) ex(p->opr.op[1]); return 0;
        case IF:        if (ex(p->opr.op[0]))
                            ex(p->opr.op[1]);
                        else if (p->opr.nops > 2)
                            ex(p->opr.op[2]);
                        return 0;
		case SWITCH:	;
						int switch_val = ex(p->opr.op[0]);
						nodeType* cases = p->opr.op[1];
						nodeType* def_leaf = NULL;
						int i = 0;
						while(cases) {
							printf("Itr: %d, type: %d\n", i, cases->opr.oper);
							nodeType* leaf_case;
							if (cases->opr.oper == '_') {
								leaf_case = cases->opr.op[0];
								if (ex(leaf_case->opr.op[0])	 == switch_val)
									leaf_case->opr.op[1];
								else
									break;
							}
							else if (cases->opr.oper == '#') {
								leaf_case = cases->opr.op[1];
								if (leaf_case->opr.oper == DEFAULT) {
									def_leaf = leaf_case;
									cases = cases->opr.op[0];
								}
								else if (ex(leaf_case->opr.op[0]) == switch_val) {
									ex(leaf_case->opr.op[1]);
									return 0;
								}
								else
									cases = cases->opr.op[0];
							}
							else {
								printf("We're here by mistake\n");
								cases = cases->opr.op[0];
							}
							i++;
						}
						if (def_leaf != NULL)
							ex(def_leaf);
						return 0;
		case FOR:		for(int i = ex(p->opr.op[0]); i < ex(p->opr.op[1]); ex(p->opr.op[2]))
							return ex(p->opr.op[4]);
		case CASE:		ex(p->opr.op[1]);
						return 0;
		case DEFAULT:	ex(p->opr.op[0]);
						return 0;
		case '#':		return ex(p->opr.op[0]);
        case PRINT:     printf("%d\n", ex(p->opr.op[0])); return 0;
        case ';':       ex(p->opr.op[0]); return ex(p->opr.op[1]);
		case '_':		return ex(p->opr.op[0]);
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
		case AND:		return ex(p->opr.op[0]) && ex(p->opr.op[1]);
		case OR:		return ex(p->opr.op[0]) || ex(p->opr.op[1]);
		case BIT_AND:	return ex(p->opr.op[0]) & ex(p->opr.op[1]);
		case BIT_OR:	return ex(p->opr.op[0]) | ex(p->opr.op[1]);
		case BIT_XOR:	return ex(p->opr.op[0]) ^ ex(p->opr.op[1]);
		case BIT_NOT:	return ~ex(p->opr.op[0]);
		case L_SHIFT:	return ex(p->opr.op[0]) << ex(p->opr.op[1]);
		case R_SHIFT:	return ex(p->opr.op[0]) >> ex(p->opr.op[1]);
		case POST_INC:	return sym[p->opr.op[0]->id.i] += 1;
		case POST_DEC:	return sym[p->opr.op[0]->id.i] -= 1;
		case PRE_INC:	return sym[p->opr.op[0]->id.i] += 1;
		case PRE_DEC:	return sym[p->opr.op[0]->id.i] -= 1;
        }
    }
    return 0;
}

void print_node(nodeType* node) {
	printf("Node type: %d\nOper: %d\n", node->type, node->opr.oper);
	printf("Operands: %d\n", node->opr.nops);
	return;
	
	for (int i = 0; i < node->opr.nops; i++) {
		printf("Type: %d", node->opr.op[i]->type);
	}
	
}