#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symboltable.h"
#include "ast.h"
#include "simplify.h"

void printChar(AST r)
{
	if(r->kind == NUMBER_NK)
	{
		printf("%d\n",r->fields.intval);
	}
	else if(r->kind == CHARCONST_NK)
	{
		if(strcmp(r->fields.stringval,"\n") == 0)
			printf("\n");
		else if(strcmp(r->fields.stringval,"\\") == 0)
			printf("\\");
		else				
			printf("%s",r->fields.stringval);
	}
	else if(r->kind == BOOL_NK)
	{
		if(r->extra == BOOL_TRUE)
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
	else
		printf("Not a int/char/bool type, cannot print\n");
}

AST performAction(AST t)
{
	AST s = t;
	if(s->kind == ACTION_NK)
	{
		AST x = performAction(s->fields.subtrees.s1);
		AST y = applyNode(s->fields.subtrees.s2,x);
		return performAction(y);
	}
	if(s->kind == BASIC_FUNC_NK)
	{
		if(s->extra == PRILST_FK)
		{
			AST x= simplify(s->fields.subtrees.s1);
			while(x->kind != EMPTYLIST)
			{
				AST y = applyBasicFunc(x,"head");
				printChar(simplify(y));
				y = applyBasicFunc(x,"tail");
				x = simplify(y);
			}
			return emptyList();
		}
		else if(s->extra == PRINT_FK)
		{
			AST r = simplify(s->fields.subtrees.s1);
			printChar(r);
			return emptyList();
		}
		else if(s->extra == PROD_FK)
		{
			return simplify(s->fields.subtrees.s1);
		}
		else if(s->extra == READI_FK)
		{
			char str[33];
			if(fgets(str,33,stdin) != NULL)		
				return numberNode(atoi(str));
			else
				return errorNode("Not a valid number");
		}
		else if(s->extra == READC_FK)
		{
			char str[2];
			if(fgets(str,2,stdin) != NULL)		
				return charNode(str);
			else
				return errorNode("Not a valid character");
		}
		else
		{
			return errorNode("No action specified");
		}
	}
	else
	{
		return errorNode("No action specified");
	}

}

int interpreter(void)
{
	AST M = getTree("main");
	AST R = simplify(M);
	
	if((R->kind == ACTION_NK) ||
	   ((R->kind == BASIC_FUNC_NK) &&
	   	((R->extra == PRILST_FK) ||
		(R->extra == PRINT_FK) ||
		(R->extra == PROD_FK) ||
		(R->extra == READI_FK) ||
		(R->extra == READC_FK))))
	{
		AST ret = performAction(R);
		if(ret->kind == ERROR_NK)
		{
			return 1;
		}
		else if(ret->kind != EMPTYLIST)
		{
			displayAST(ret);
		}
	} 
	else
		displayAST(R);
	return 0;
}
