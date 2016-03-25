#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symboltable.h"
#include "simplify.h"

AST getHead(AST t)
{
	AST s = simplify(t);
	while((s->kind != NUMBER_NK) &&
	      (s->kind != CHARCONST_NK) &&
	      (s->kind != BOOL_NK))
	      s = s->fields.subtrees.s1;
	
	return s;	
}

AST buildTail(AST t)
{
	AST s = NEW(ASTNODE);
	s->kind = t->kind;
	s->fields.subtrees.s1 = t->fields.subtrees.s1;
	s->fields.subtrees.s2 = t->fields.subtrees.s2;
	if(t->fields.subtrees.s1->kind != CONS_NK)
		return s->fields.subtrees.s2;
	else
	{
		s->fields.subtrees.s1 = buildTail(s->fields.subtrees.s1);		
		return s;
	}
}

VL headptr;

int getVal(int x)
{
	VL tmpptr = headptr;
	if(tmpptr == NULL)
		return -1;
	else
	{
		while(tmpptr != NULL)
		{
			if(tmpptr->oldval == x)
				return tmpptr->newval;
			else
				tmpptr = tmpptr->next;
		}
		return -1;
	}
}

VL newValNode(VL inPtr, int val)
{
	VL vn = NEW(VALNODE);
	vn->next = inPtr;
	vn->oldval = val;
	vn->newval = val + 1000;
	return vn;
}

void scanTree(AST r)
{
	if(r != NULL)
	{
		if(r->kind == FUNC_NK)
		{
			if(getVal(r->extra) == -1)
			{
				headptr = newValNode(headptr, r->extra);
				scanTree(r->fields.subtrees.s1);
			}
			else
			{
				//Error duplicate function
			}
		}
		else if(r->kind == OP_NK)
		{
			AST z = getTree(r->fields.stringval);
			scanTree(z);
		}
		else if((r->kind == BASIC_FUNC_NK) || (r->kind == OP_NK) || (r->kind == APPLY_NK)
			|| (r->kind == BRANCH_NK) || (r->kind == ACTION_NK) || (r->kind == COLON_NK)
			|| (r->kind == CONS_NK))
		{
			scanTree(r->fields.subtrees.s1);
			scanTree(r->fields.subtrees.s2);
			scanTree(r->fields.subtrees.s3);	
		}
	}
}

void deleteValList(VL ptr)
{
	if(ptr != NULL)
	{
		deleteValList(ptr->next);
		free(ptr);
	}
}	

AST copyTree(AST r, AST s, int x)
{
	headptr = NULL;
	scanTree(r);
	AST t = copyAST(r,s,x);
	deleteValList(headptr);
	headptr = NULL;
	return t;
}

AST copyAST(AST r, AST s, int x)
{
	if(r == NULL)
	{
		return NULL;
	}
	else if(r->kind == FUNC_NK)
	{
		int nv = getVal(r->extra);
		if(nv != -1)
		{
			AST z = NEW(ASTNODE);
			z->kind = r->kind;
			z->extra = nv;
			z->fields.subtrees.s1 = copyAST(r->fields.subtrees.s1,s,x);
			return z;
		}
		else
		{
			return errorNode("error");
		}
		
	}
	else if(r->kind == PARAM_NK)
	{
		if(r->fields.intval == x)		
			return s;
		else
		{
			int nv = getVal(r->fields.intval);
			if(nv != -1)
			{
				return applyParam(nv);
			}
			else
			{
				//parm value does not exist
				return errorNode("Parameter value does not exist");
			}
		}
	}
	else if(r->kind == OP_NK)
	{
		AST z = NEW(ASTNODE);
		z->kind = r->kind;
		z->extra = r->extra;
		z->fields.subtrees.s1 = copyAST(r->fields.subtrees.s1,s,x);
		z->fields.subtrees.s2 = copyAST(r->fields.subtrees.s2,s,x);
		return z;		
	}
	else if(r->kind == NUMBER_NK)
	{
		AST z = NEW(ASTNODE);
		z->kind = r->kind;
		z->fields.intval = r->fields.intval;
		return z;
	}
	else if(r->kind == APPLY_NK)
	{
		AST z = NEW(ASTNODE);
		z->kind = r->kind;
		z->fields.subtrees.s1 = copyAST(r->fields.subtrees.s1,s,x);
		z->fields.subtrees.s2 = copyAST(r->fields.subtrees.s2,s,x);
		return z;		
	}
	else if(r->kind == ID_NK)
	{
		AST z = copyAST(getTree(r->fields.stringval),s,x);
		return z;
	}
	else if((r->kind == CHARCONST_NK))
	{
		AST z = NEW(ASTNODE);
		z->kind = r->kind;
		z->fields.stringval = r->fields.stringval;
		return z;		
	}
	else if(r->kind == BRANCH_NK)
	{
		AST z = NEW(ASTNODE);
		z->kind = r->kind;
		z->fields.subtrees.s1 = copyAST(r->fields.subtrees.s1,s,x);
		z->fields.subtrees.s2 = copyAST(r->fields.subtrees.s2,s,x);
		z->fields.subtrees.s2 = copyAST(r->fields.subtrees.s3,s,x);
		return z;		
	}
	else if(r->kind == BASIC_FUNC_NK)
	{
		AST z = NEW(ASTNODE);
		z->kind = r->kind;
		z->extra = r->extra;
		z->fields.subtrees.s1 = copyAST(r->fields.subtrees.s1,s,x);
		return z;		
	}
	else if((r->kind == COLON_NK) || (r->kind == CONS_NK) || (r->kind == ACTION_NK))
	{
		AST z = NEW(ASTNODE);
		z->kind = r->kind;
		z->extra = r->extra;
		z->fields.subtrees.s1 = copyAST(r->fields.subtrees.s1,s,x);
		z->fields.subtrees.s2 = copyAST(r->fields.subtrees.s2,s,x);
		return z;		
	}
	else if(r->kind == BOOL_NK)
	{
		AST z = NEW(ASTNODE);
		z->kind = r->kind;
		z->extra = r->extra;
		return z;		
	}
	else if(r->kind == EMPTYLIST)
	{
		AST z = NEW(ASTNODE);
		z->kind = r->kind;
		return z;		
	}	
	else
		return NULL;
}

AST applyValue(AST r, AST s)
{
	int i;
	i = r->extra;
	return copyTree(r->fields.subtrees.s1, s, i);
	
}

AST simplify(AST t)
{
	AST ret = NULL;
	if(t != NULL)
	{
		if(t->kind == ID_NK)
			ret = getTree(t->fields.stringval);
		else if((t->kind == NUMBER_NK) || (t->kind == CHARCONST_NK)
			 || (t->kind == EMPTYLIST) || (t->kind == BOOL_NK))  
			ret = t; 
		else if(t->kind == CONS_NK)
			ret = t;
		else if(t->kind == COLON_NK)
		{	
			AST s = simplify(t->fields.subtrees.s1);
			AST r = simplify(t->fields.subtrees.s2);
			if(s->kind == ERROR_NK)
				ret = errorNode(s->fields.stringval);
			else if(r->kind == ERROR_NK)
				ret = errorNode(s->fields.stringval);
			else			
				ret = applyCONS(s, r);
		}
		else if(t->kind == BRANCH_NK)
		{
			AST s = simplify(t->fields.subtrees.s1);
			AST r = simplify(t->fields.subtrees.s2);
			AST u = simplify(t->fields.subtrees.s3);
			if(s->kind == ERROR_NK)
				ret = errorNode(s->fields.stringval);
			else if(r->kind == ERROR_NK)
				ret = errorNode(r->fields.stringval);
			else if(u->kind == ERROR_NK)
				ret = errorNode(u->fields.stringval);
			else if(s->kind == BOOL_NK)
			{
				if(s->extra == BOOL_TRUE)
					ret = r;
				else
					ret = u;
			}
			else
			{
				ret = errorNode("Conditional does not resolve into a boolean value");
			}
		}
		else if(t->kind == OP_NK)
		{
			AST s = simplify(t->fields.subtrees.s1);
			AST r = simplify(t->fields.subtrees.s2);
			if(s->kind == ERROR_NK)
				ret = errorNode(s->fields.stringval);
			else if(r->kind == ERROR_NK)
				ret = errorNode(s->fields.stringval);
			else
			{
			if(t->extra == PLUSOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					int x = s->fields.intval + r->fields.intval;
					ret = numberNode(x);
				}
				else
				{
					ret = errorNode("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra == SUBOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					int x = s->fields.intval - r->fields.intval;
					ret = numberNode(x);
				}
				else
				{
					ret = errorNode("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra == MULTOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					int x = s->fields.intval * r->fields.intval;
					ret = numberNode(x);
				}
				else
				{
					ret = errorNode("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra == DIVOP_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					if(r->fields.intval == 0)
						ret = errorNode("Divide by zero error");
					else	
					{
						int x = s->fields.intval / r->fields.intval;
						ret = numberNode(x);
					}
				}
				else
				{
					ret = errorNode("Operand is not the correct type, must be an integer type");
				}
			}
			else if(t->extra == ANDOP_OK)
			{
				if((s->kind == BOOL_NK) && (r->kind == BOOL_NK))
				{
					if((s->extra == BOOL_TRUE) && (r->extra == BOOL_TRUE))
					{
						ret = boolNode("true");
					}
					else
					{
						ret = boolNode("false");
					}
				}
				else
				{
					ret = errorNode("Operand is not the correct type, must be a boolean type");
				}
			}
			else if(t->extra == OROP_OK)
			{
				if((s->kind == BOOL_NK) && (r->kind == BOOL_NK))
				{
					if((s->extra == BOOL_TRUE) || (r->extra == BOOL_TRUE))
					{
						ret = boolNode("true");
					}
					else
					{
						ret = boolNode("false");
					}
				}
				else
				{
					ret = errorNode("Operand is not the correct type, must be a boolean type");
				}
			}
			else if(t->extra == NOTOP_OK)
			{
				if(s->kind == BOOL_NK)
				{
					if(s->extra == BOOL_TRUE)
					{
						ret = boolNode("false");
					}
					else
					{
						ret = boolNode("true");
					}
				}
				else
				{
					ret = errorNode("Operand is not the correct type, must be a boolean type");
				}
			}
			else if(t->extra == GT_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					if(s->fields.intval > r->fields.intval)
						ret = boolNode("true");
					else					
						ret = boolNode("false");
				}
				else
				{
					ret = errorNode("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra == LT_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					if(s->fields.intval < r->fields.intval)
						ret = boolNode("true");
					else
						ret = boolNode("false");
				}				
				else
				{
					ret = errorNode("Operand is not the correct type, must be an integer");
				}
			}
			else if(t->extra == EQ_OK)
			{
				if((s->kind == NUMBER_NK) && (r->kind == NUMBER_NK))
				{
					if(s->fields.intval == r->fields.intval)
						ret = boolNode("true");
					else
						ret = boolNode("false");
				}
				else if((s->kind == BOOL_NK) && (r->kind == BOOL_NK))
				{
					if(s->extra < r->extra)
						ret = boolNode("true");
					else
						ret = boolNode("false");
				}
				else if((s->kind == CHARCONST_NK) && (r->kind == CHARCONST_NK))
				{
					if(strcmp(s->fields.stringval,r->fields.stringval) == 0)
						ret = boolNode("true");
					else
						ret = boolNode("false");
				}
				else
				{
					ret = errorNode("Operand is not the correct type, must be an integer");
				}
			}
			}
		}
		else if(t->kind == BASIC_FUNC_NK)
		{
			if(t->extra == ISINT_FK)
			{
				AST s = simplify(t->fields.subtrees.s1);
				if(s->kind == ERROR_NK)
					ret = errorNode(s->fields.stringval);
				else if(s->kind == NUMBER_NK)
					ret = boolNode("true");
				else
					ret = boolNode("false");
			}
			else if(t->extra == ISBOOL_FK)
			{
				AST s = simplify(t->fields.subtrees.s1);
				if(s->kind == ERROR_NK)
					ret = errorNode(s->fields.stringval);
				else if(s->kind == BOOL_NK)
					ret = boolNode("true");
				else
					ret = boolNode("false");
			}
			else if(t->extra == ISLIST_FK)
			{
				AST s = simplify(t->fields.subtrees.s1);
				if(s->kind == ERROR_NK)
					ret = errorNode(s->fields.stringval);
				else if((s->kind == CONS_NK) || (s->kind == EMPTYLIST))
					ret = boolNode("true");
				else
					ret = boolNode("false");
			}
			else if(t->extra == ISCHAR_FK)
			{
				AST s = simplify(t->fields.subtrees.s1);
				if(s->kind == ERROR_NK)
					ret = errorNode(s->fields.stringval);
				else if(s->kind == CHARCONST_NK)
					ret = boolNode("true");
				else
					ret = boolNode("false");
			}
			else if(t->extra == ISFUNC_FK)
			{
				AST s = simplify(t->fields.subtrees.s1);
				if(s->kind == ERROR_NK)
					ret = errorNode(s->fields.stringval);
				else if((s->kind == FUNC_NK) || (s->kind == BASIC_FUNC_NK))
					ret = boolNode("true");
				else
					ret = boolNode("false");
			}
			else if(t->extra == ISACTION_FK)
			{
				AST s = simplify(t->fields.subtrees.s1);
				if(s->kind == ERROR_NK)
					ret = errorNode(s->fields.stringval);
				else if(s->kind == ACTION_NK)				
					ret = boolNode("true");
				else
					ret = boolNode("false");
			}
			else if(t->extra == ISNULL_FK)
			{
				AST s = simplify(t->fields.subtrees.s1);
				if(s->kind == ERROR_NK)
					ret = errorNode(s->fields.stringval);
				else if(s->kind == EMPTYLIST)
					ret = boolNode("true");
				else
					ret = boolNode("false");
			}
			else if(t->extra == HEAD_FK)
			{
				AST s = simplify(t->fields.subtrees.s1);
				if(s->kind == ERROR_NK)
					ret = errorNode(s->fields.stringval);
				else if(s->kind == EMPTYLIST)
					ret = errorNode("Cannot return the head of an empty list");
				else if(s->kind != CONS_NK)
					ret = errorNode("Cannot return the head of an non-list");
				else
					ret = getHead(s);				
			}
			else if(t->extra == TAIL_FK)
			{
				AST s = simplify(t->fields.subtrees.s1);
				if(s->kind == ERROR_NK)
					ret = errorNode(s->fields.stringval);
				else if(s->kind == EMPTYLIST)
					ret = errorNode("Cannot return the tail of an empty list");
				else if(s->kind != CONS_NK)
					ret = errorNode("Cannot return the tail of an non-list");
				else
					ret = buildTail(s);
			}
			else if((t->extra == READI_FK) || (t->extra == READC_FK))
			{
				ret = t;
			}
			else if((t->extra == PRINT_FK) || (t->extra == PRILST_FK) || (t->extra == PROD_FK))
			{
				ret = t;
			}
			
			
		}
		else if(t->kind == ACTION_NK)
		{
			ret = t;
		}
		else if(t->kind == FUNC_NK)
		{
			ret = t;
		}
		else if(t->kind == APPLY_NK)
		{
				AST r = simplify(t->fields.subtrees.s1);
				if(r->kind != FUNC_NK)
				{
					ret = errorNode("Cannot apply a value to a non-funtion");
				}
				else
				{
					AST s = simplify(t->fields.subtrees.s2);
					if(s->kind == ERROR_NK)
						ret = errorNode(s->fields.stringval);
					else 					
						ret = simplify(applyValue(r,s));
				}
		}
		else
			ret = errorNode("Unknown token value");

	}
	return ret;

}
