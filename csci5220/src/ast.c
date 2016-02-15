#include <stdio.h>
#include "ast.h"
#include "allocate.h"

AST numberNode(int n)
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
	t->fields.stringval = s;

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


AST applyOp(AST A, AST B, char opKind)
{
	AST t = NEW(ASTNODE);
	int op;
	t->kind = OP_NK;
	
	if(opKind == '+') 
		op = PLUSOP_OK;
	else if(opKind == '*')
		op = MULTOP_OK;
	t->extra = op;	
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

AST applyCond(AST A, AST B, AST C, int CondKind)
{
	AST t = NEW(ASTNODE);
	t->kind = IFOP_NK;
	t->extra = CondKind;
	t->fields.subtrees.s1 = A;
	t->fields.subtrees.s2 = B;
	t->fields.subtrees.s3 = C;
	return t;
}

AST applyFunc(AST A, int FuncKind)
{
	AST t = NEW(ASTNODE);
	t->kind = BASIC_FUNC_NK;
	t->extra = FuncKind;
	t->fields.subtrees.s1 = A;
	return t;
}

void displayAST(AST A)
{
	if(A->kind == NUMBER_NK)
		printf("  %d\n",A->fields.intval);
	else if(A->kind == ID_NK)
		printf("  %s\n",A->fields.stringval);
	else
 	{

	if(A->extra == PLUSOP_OK)
		printf("+\n");
	else if(A->extra == MULTOP_OK)
		printf("*\n");

	if(A->fields.subtrees.s1 != '\0')
		displayAST(A->fields.subtrees.s1);
	if(A->fields.subtrees.s2 != '\0')
		displayAST(A->fields.subtrees.s2);
	if(A->fields.subtrees.s3 != '\0')
		displayAST(A->fields.subtrees.s3);
	}
}
	
