#ifndef AST_H_
#define AST_H_



#define NUMBER_NK	1
#define APPLY_NK 	2
#define ID_NK		3
#define OP_NK		4

#define PLUSOP_OK       40
#define SUBOP_OK	41
#define MULTOP_OK	42
#define DIVOP_OK	43
#define GT_OK		44
#define LT_OK		45
#define EQ_OK		46
#define ANDOP_OK	47
#define OROP_OK		48
#define NOTOP_OK	49
#define SEMICOL_OK	50

#define IFOP_NK		5
#define IF_OK		51
#define ELSE_OK		52

#define BASIC_FUNC_NK	6
#define ISNULL_FK	60
#define ISFUNC_FK	61
#define ISINT_FK	62
#define ISBOOL_FK	63
#define ISACTION_FK	64
#define ISCHAR_FK	65
#define HEAD_FK		66
#define TAIL_FK		67
#define PRINT_FK	68
#define PRILST_FK	69
#define PROD_FK		70
#define READC_FK	71
#define READI_FK	72



#define COLON_NK 	7
#define CONS_NK		8

typedef struct astnode {
	int kind;
	int mark;
	int extra;
	
	union {
		int intval;
		const char* stringval;
		struct {
			struct astnode* s1;
			struct astnode* s2;
			struct astnode* s3;
		} subtrees;
	} fields;
}
ASTNODE;

typedef ASTNODE* AST;
int charpad;

AST numberNode(int n);

AST applyOp(AST A, AST B, char opKind);

void displayAST();
#endif
