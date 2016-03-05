#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "simplify.h"
#include "symboltable.h"

AST simplify(AST t)
{
	if(t != NULL)
	{
		if(t->kind == ID_NK)
			return getTree(t->subtrees.stringval);
		else if((t->kind == NUMBER_NK) || (t->kind == CONSTCHAR_NK)
			 || (t->kind == EMPTYLIST) || (t->kind == BOOL_NK))  
			return t; 
		else if(t->kind == CONS_NK)
			return t;
		else if(t->kind == COLON_NK)
		{
			return applyCONS(simplify(t->subtrees.s1), simplify(t->subtrees.s2));
		}
		else if(t->kind == OP_NK)
		{
			AST s = simplify(t->subtrees.s1);
			AST r = simplify(t->subtrees.s2);
			if(t->extra = PLUSOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					int x = s->subtrees.intval + r->subtrees.intval;
					return numberNODE(x);
				}
				else
				{
					return errorNODE("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra = SUBOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					int x = s->subtrees.intval - r->subtrees.intval;
					return numberNODE(x);
				}
			}
			else if(t->extra = MULTOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					int x = s->subtrees.intval * r->subtrees.intval;
					return numberNODE(x);
				}
			}
			else if(t->extra = DIVOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					int x = s->subtrees.intval / r->subtrees.intval;
					return numberNODE(x);
				}
			}
		}

	}
	return NULL;

}
