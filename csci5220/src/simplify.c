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
		else if(t->kind == BRANCH_NK)
		{
			AST s = simplify(t->subtrees.s1);
			AST r = simplify(t->subtrees.s2);
			AST u = simplify(t->subtrees.s3);
			
			if(s->kind == BOOL_NK)
			{
				if(s->extra == BOOL_TRUE)
					return r;
				else
					return u;
			}
			else
			{
				return errorNODE("Conditional does not resolve into a boolean value");
			}
		}
		else if(t->kind == OP_NK)
		{
			AST s = simplify(t->subtrees.s1);
			AST r = simplify(t->subtrees.s2);
			AST u = simplify(t->subtrees.s3);
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
				else
				{
					return errorNODE("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra = MULTOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					int x = s->subtrees.intval * r->subtrees.intval;
					return numberNODE(x);
				}
				else
				{
					return errorNODE("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra = DIVOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					if(r->subtrees.intval == 0)
						return errorNode("Divide by zero error");
						
					int x = s->subtrees.intval / r->subtrees.intval;
					return numberNODE(x);
				}
				else
				{
					return errorNODE("Operand is not the correct type, must be an integer type");
				}
			}
			else if(t->extra == ANDOP_OK)
			{
				if((s->kind == BOOL_NK) && (r->kind == BOOL_NK))
				{
					if((s->extra == BOOL_TRUE) && (r->extra == BOOL_TRUE))
					{
						return boolNode("true");
					}
					else
					{
						return boolNode("false");
					}
				}
				else
				{
					return errorNODE("Operand is not the correct type, must be a boolean type");
				}
			}
			else if(t->extra == OROP_OK)
			{
				if((s->kind == BOOL_NK) && (r->kind == BOOL_NK))
				{
					if((s->extra == BOOL_TRUE) || (r->extra == BOOL_TRUE))
					{
						return boolNode("true");
					}
					else
					{
						return boolNode("false");
					}
				}
				else
				{
					return errorNODE("Operand is not the correct type, must be a boolean type");
				}
			}
			else if(t->extra == NOTOP_OK)
			{
				if(s->kind == BOOL_NK)
				{
					if(s->extra == BOOL_TRUE)
					{
						return boolNode("false");
					}
					else
					{
						return boolNode("true");
					}
				}
				else
				{
					return errorNODE("Operand is not the correct type, must be a boolean type");
				}
			}
			else if(t->extra == GT_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					if(s->subtree.intval > r->subtree.intval)
						return boolNode("true");
					else
						return boolNode("false");
				else
				{
					return errorNODE("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra == LT_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					if(s->subtree.intval < r->subtree.intval)
						return boolNode("true");
					else
						return boolNode("false");
				else
				{
					return errorNODE("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra == EQ_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					if(s->subtree.intval == r->subtree.intval)
						return boolNode("true");
					else
						return boolNode("false");
				else
				{
					return errorNODE("Operand is not the correct type, must be an integer");
				}
			}
		}
		if(t->kind == BASIC_FUNC_NK)
		{
			if(t->extra == ISINT_FK)
			{
				AST s = simplify(t->subtrees.s1);
				if(s->kind == NUMBER_NK)
					return boolNode("true");
				else
					return boolNode("false");
			}
			else if(t->extra == ISBOOL_FK)
			{
				AST s = simplify(t->subtrees.s1);
				if(s->kind == BOOL_NK)
					return boolNode("true");
				else
					return boolNode("false");
			}
			else if(t->extra == ISLIST_FK)
			{
				AST s = simplify(t->subtrees.s1);
				if(s->kind == CONS_NK)
					return boolNode("true");
				else
					return boolNode("false");
			}
			else if(t->extra == ISCHAR_FK)
			{
				AST s = simplify(t->subtrees.s1);
				if(s->kind == CHARCONST_NK)
					return boolNode("true");
				else
					return boolNode("false");
			}
			else if(t->extra == ISFUNC_FK)
			{
				AST s = simplify(t->subtrees.s1);
				if((s->kind == FUNC_NK) || (s->kind == BASIC_FUNC_NK))
					return boolNode("true");
				else
					return boolNode("false");
			}
			else if(t->extra == ISACTION_FK)
			{
				AST s = simplify(t->subtrees.s1);
				if(s->kind == PRODUCE_NK)
				{
					return boolNode("true");
				else
					return boolNode("false");
			}
			else if(t->extra == ISNULL_FK)
			{
				AST s = simplify(t->subtrees.s1);
				if((s->kind == EMPTYLIST)
					return boolNode("true");
				else
					return boolNode("false");
			}
			else if(t->extra == HEAD_NK)
			{return false;}
			else if(t->extra == TAIL_NK)
			{return false;}
			else if((t->extra == READINT_NK) || (t->extra == READCHAR_NK))
			{
				return t;
			}
			
			
		}

	}
	return NULL;

}
