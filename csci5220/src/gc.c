#include "ast.h"
#include "gc.h"
#include "allocate.h"
#include <stdio.h>


AST freelist;
ASTTABLE astMem;

void abortCollect(void)
{
	printf("Error: Unable to allocate any more AST nodes\n");
	exit(-1);
}

AST addFreeNode(AST list, AST node)
{
	AST tmpptr = node;
	tmpptr->fields.subtrees.s1 = list;
	return tmpptr;
}

void initialize_gc(void)
{
	int x;
	astMem = NEWARRAY(AST, AST_MEM_SIZE);

	for(x = 0; x < AST_MEM_SIZE; x++)
	{
		astMem[x] = NEW(ASTNODE);
		freelist = addFreeNode(freelist,astMem[x]);
	}
}

AST returnHead(void)
{
	AST tmpptr = freelist;
	freelist = freelist->fields.subtrees.s1;
	return tmpptr;
}

AST getNewAST()
{
	if(freelist == NULL)
	{
		if(garbageCollect() == 0)
			return returnHead();
		else
		{
			abortCollect();
			return NULL;
		}
	}
	else
		return returnHead();
}

void mark(AST t)
{
	if(t == NULL)
		return;
	else
	{
	 	t->mark = 1;
	 	switch(t->kind)
	 	{
			case BRANCH_NK :
				mark(t->fields.subtrees.s1);
				mark(t->fields.subtrees.s2);
				mark(t->fields.subtrees.s3);
				break;
			case FUNC_NK :
				mark(t->fields.subtrees.s1);
				break;
			case BASIC_FUNC_NK :
				mark(t->fields.subtrees.s1);
				break;
			case COLON_NK :
				mark(t->fields.subtrees.s1);
				mark(t->fields.subtrees.s2);
				break;
			case CONS_NK :
				mark(t->fields.subtrees.s1);
				mark(t->fields.subtrees.s2);
				break;
			case OP_NK :
				mark(t->fields.subtrees.s1);
				mark(t->fields.subtrees.s2);
				break;
			case ACTION_NK :
				mark(t->fields.subtrees.s1);
				mark(t->fields.subtrees.s2);
				break;
			default :
				break;
		}
	}	
}

			
void markALL(AST t)
{
	mark(t);	
}

int garbageCollect()
{
	int x;
	for(x = 0; x < AST_MEM_SIZE-1; x++)
	{
		if(astMem[x] != NULL)
			astMem[x]->mark = 0;
	}
	return 0;
}
		
