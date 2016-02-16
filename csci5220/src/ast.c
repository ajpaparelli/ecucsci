#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "stringtable.h"
#include "allocate.h"

char* getBoolName(const int i)
{
	if(i == BOOL_TRUE)
		return "true";
	else if(i == BOOL_FALSE)
		return "false";
	else	
		return "\0";
}

int getBoolDef(const char* s)
{
	if(strcmp(s,"true") == 0)
		return BOOL_TRUE;
	else if(strcmp(s,"false") == 0)
		return BOOL_FALSE;
	else
		return -1;
}

char* getOperatorName(const int i)
{
	if(i == 40)
		return "+";
	else if(i == 41)
		return "-";
	else if(i == 42)
		return "*";
	else if(i == 43)
		return "/";
	else if(i == 44)
		return ">";
	else if(i == 45)
		return "<";
	else if(i == 46)
		return "==";
	else if(i == 47)
		return "and";
	else if(i == 48)
		return "or";
	else if(i == 49)
		return "not";
	else
		return "\0";
}

int getOperatorDef(const char* c)
{
	if(strcmp(c,"+") == 0)
		return PLUSOP_OK;
	else if(strcmp(c,"-") == 0)
		return SUBOP_OK;
	else if(strcmp(c,"*") == 0)
		return MULTOP_OK;
	else if(strcmp(c,"/") == 0)
		return DIVOP_OK;
	else if(strcmp(c,">") == 0)
		return GT_OK;
	else if(strcmp(c,"<") == 0)
		return LT_OK;
	else if(strcmp(c,"==") == 0)
		return EQ_OK;
	else if(strcmp(c,"and") == 0)
		return ANDOP_OK;
	else if(strcmp(c,"or") == 0)
		return OROP_OK;
	else if(strcmp(c,"not") == 0)
		return NOTOP_OK;
	else
		return -1;
}

char* getFunctionName(const int n)
{
	if(n == ISNULL_FK)
		return "isNull";
	else if(n == ISFUNC_FK)
		return "isFunc";
	else if(n == ISINT_FK)
		return "isInt";
	else if(n == ISBOOL_FK)
		return "isBool";
	else if(n == ISACTION_FK)
		return "isAction";
	else if(n == ISCHAR_FK)
		return "isChar";
	else if(n == HEAD_FK)
		return "head";
	else if(n == TAIL_FK)
		return "tail";
	else if(n == PRINT_FK)
		return "print";
	else if(n == PRILST_FK)
		return "printList";
	else if(n == PROD_FK)
		return "produce";
	else if(n == READC_FK)
		return "readChar";
	else if(n == READI_FK)
		return "readInt";
	else
		return "\0";
}

int getFunctionDef(const char* s)
{	
	if(strcmp(s,"isNull") == 0)
		return ISNULL_FK;
	else if(strcmp(s,"ifFunc") == 0)
		return ISFUNC_FK;
	else if(strcmp(s,"ifInt") == 0)
		return ISINT_FK;
	else if(strcmp(s,"isBool") == 0)
		return ISBOOL_FK;
	else if(strcmp(s,"isAction") == 0)
		return ISACTION_FK;
	else if(strcmp(s,"isChar") == 0)
		return ISCHAR_FK;
	else if(strcmp(s,"head") == 0)
		return HEAD_FK;
	else if(strcmp(s,"tail") == 0)
		return TAIL_FK;
	else if(strcmp(s,"print") == 0)
		return PRINT_FK;
	else if(strcmp(s,"printList") == 0)
		return PRILST_FK;
	else if(strcmp(s,"produce") == 0)
		return PROD_FK;
	else if(strcmp(s,"readChar") == 0)
		return READC_FK;
	else if(strcmp(s,"readInt") == 0)
		return READI_FK;
	else
		return -1;
}

AST numberNode(const int n)
{
	AST t = NEW(ASTNODE);
	t->kind = NUMBER_NK;
	t->fields.intval = n;
	return t;
}

AST idNode(const char* s)
{
	AST t = NEW(ASTNODE);
	t->kind = ID_NK;
	t->fields.stringval = intern(s);
	return t;
}

AST boolNode(const char* s)
{
	AST t = NEW(ASTNODE);
	t->kind = BOOL_NK;
	t->extra = getBoolDef(s);
	return t;
}

AST emptyList()
{
	AST t= NEW(ASTNODE);
	t->kind = EMPTYLIST;
	return t;
}

AST applyNode(AST A, AST B)
{
	AST t = NEW(ASTNODE);
	t->kind = APPLY_NK;
	t->fields.subtrees.s1 = A;
	t->fields.subtrees.s2 = B;	
	return t;
}


AST applyOp(AST A, AST B, char* opKind)
{
	AST t = NEW(ASTNODE);
	t->kind = OP_NK;
	t->extra = getOperatorDef(opKind);	
	t->fields.subtrees.s1 = A;
	t->fields.subtrees.s2 = B;
	return t;
}

AST applyCOLON(AST A, AST B)
{
	AST t = NEW(ASTNODE);
	t->kind = COLON_NK;
	t->fields.subtrees.s1 = A;
	t->fields.subtrees.s2 = B;
	return t;
}

AST applyCONS(AST A, AST B)
{
	AST t = NEW(ASTNODE);
	t->kind = CONS_NK;
	t->fields.subtrees.s1 = A;
	t->fields.subtrees.s2 = B;
	return t;
}

AST applyBranch(AST A, AST B, AST C)
{
	AST t = NEW(ASTNODE);
	t->kind = BRANCH_NK;
	t->fields.subtrees.s1 = A;
	t->fields.subtrees.s2 = B;
	t->fields.subtrees.s3 = C;
	return t;
}

AST applyBasicFunc(AST A, const char* FuncKind)
{
	AST t = NEW(ASTNODE);
	t->kind = BASIC_FUNC_NK;
	t->extra = getFunctionDef(FuncKind);
	t->fields.subtrees.s1 = A;
	return t;
}

AST applyProd(AST A, AST B)
{
	AST t = NEW(ASTNODE);
	t->kind = PRODUCE_NK;
	t->fields.subtrees.s1 = A;
	t->fields.subtrees.s2 = B;
	return t;
}

AST applyFunction(AST A, const int n)
{
	AST t = NEW(ASTNODE);
	t->kind = FUNC_NK;
	t->extra = n;
	t->fields.subtrees.s1 = A;
	return t;
}

AST applyParam(const int n)
{
	AST t = NEW(ASTNODE);
	t->kind = PARAM_NK;
	t->fields.intval = n;
	return t;
}

void displayTree(AST A, int indent)
{
	int curindent = indent;
	//printf("Indent: %d \n", curindent);
	if(A->kind == EMPTYLIST)
		printf("%*s%s \n",curindent,"","[]");
	else if(A->kind == NUMBER_NK)
		printf("%*s%d \n",curindent,"",A->fields.intval);
	else if(A->kind == ID_NK)
		printf("%*s%s \n",curindent,"",A->fields.stringval);
	else if(A->kind == BOOL_NK)
		printf("%*s%s \n",curindent,"",getBoolName(A->extra));
	else if(A->kind == PARAM_NK)
		printf("%*sPARAM(%d) \n",curindent,"",A->fields.intval);
	else
 	{
		if(A->kind == COLON_NK)
			printf("%*s%s \n",curindent,"",":");
		else if(A->kind == CONS_NK)
			printf("%*s%s \n",curindent,"","CONS");
		else if(A->kind == OP_NK)
			printf("%*s%s \n",curindent,"",getOperatorName(A->extra));
		else if(A->kind == BASIC_FUNC_NK)
			printf("%*s%s \n",curindent,"",getFunctionName(A->extra));
		else if(A->kind == APPLY_NK)
			printf("%*s%s \n",curindent,"","Apply");
		else if(A->kind == PRODUCE_NK)
			printf("%*s%s \n",curindent,"","~>");
		else if(A->kind == BRANCH_NK)
			printf("%*s%s \n",curindent,"","Branch");
		else if(A->kind == FUNC_NK)
			printf("%*sFUNCTION(%d) \n",curindent,"",A->extra);


		if(A->fields.subtrees.s1 != '\0')
			displayTree(A->fields.subtrees.s1, curindent+2);
		if(A->fields.subtrees.s2 != '\0')
			displayTree(A->fields.subtrees.s2, curindent+2);
		if(A->fields.subtrees.s3 != '\0')
			displayTree(A->fields.subtrees.s3, curindent+2);
	}
}

void displayAST(AST A)
{
	displayTree(A,0);
}	
