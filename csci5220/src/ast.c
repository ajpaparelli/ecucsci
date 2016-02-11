#include "ast.h"
#include "allocate.h"

AST numberNode(int n)
{
	AST t = NEW(AST);
	t->kind = NUMBER_NK;
	t->fields.intval = n;
	return t;
}

AST idNode(const char* s)
{
	AST t = NEW(AST);
	t->kind = ID_NK;
	t->fields.stringval = s;

	return t;
}

AST applyNode(AST A, AST B)
{
	AST t = NEW(AST);
	t->kind = APPLY_NK;
	t->fields.subtrees.s1 = A;
	t->fields.subtrees.s2 = B;	
	return t;
}


AST applyOp(AST A, AST B, int OpKind)
{
	AST t = NEW(AST);
	t->kind = BASICOP_NK;
	t->extra = OpKind;
	t->fields.subtrees.s1 = A;
	t->fields.subtrees.s2 = B;
	return t;
}

AST applyCOLON(AST A, AST B)
{
	AST t = NEW(AST);
	t->kind = COLON_NK;
	t->fields.subtrees.s1 = A;
	//if(blah)
		t->fields.subtrees.s2 = B;
	//else
	//t->fields.subtrees.s2 = EMPTYLIST
	return t;
}

AST applyCONS(AST A, AST B)
{
	AST t = NEW(AST);
	t->kind = CONS_NK;
	t->fields.subtrees.s1 = A;
	//if(blah)
		t->fields.subtrees.s2 = B;
	//else
	//t->fields.subtrees.s2 = EMPTYLIST
	return t;
}

AST applyFunc(AST A, int FuncKind)
{
	AST t = NEW(AST);
	t->kind = BASIC_FUNK_NK;
	t->extra = FuncKind;
	t->fields.subtrees.s1 = A;
	return t;
}


