#ifndef AST_H_
#define AST_H_

typedef struct astnode {
	int kind;
	int mark;
	int extra;
	
	union {
		int intval;
		const char* stringval;
		struct {
			struct ast* s1;
			struct ast* s2;
			struct ast* s3;
		} subtrees;
	} fields;
}
ASTNODE;

typedef ASTNODE* AST;

#define NUMBER_NK	1
#define APPLY_NK 	2
#define ID_NK		3

#define ADDOP_NK	4
#define PLUSOP_OK       41
#define SUBOP_OK	42

#define MULOP_NK	5
#define MULTOP_OK	51
#define DIVOP_OK	52

#define RELOP_NK	6
#define GT_OK		61
#define LT_OK		62
#define EQ_OK		63

#define BASIC_FUNC_NK	7
#define ISNULL_FK	71
#define ISFUNC_FK	72
#define ISINT_FK	73
#define ISBOOL_FK	74
#define ISACTION_FK	75
#define ISCHAR_FK	76

#define BASIC_OP_NK      77

#define CONS_NK	8

#endif
