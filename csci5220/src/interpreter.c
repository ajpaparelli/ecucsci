/*

	Name: Adrian J. Paparelli
	Class: CSCI 5220
	Session: Spring 2016

	Description: interpreter.c contains all function used by the SFL interpreter. 
	Function descriptions will follow to explain each funtion.

	Change Log:
	2016-03-25: Initial Revision

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symboltable.h"
#include "ast.h"
#include "simplify.h"

/* This function used to output the contents of a number/const char/boolean node */

void printValue(AST r)
{
	if(r->kind == NUMBER_NK)
	{
		printf("%d",r->fields.intval);
	}
	else if(r->kind == CHARCONST_NK)
	{
		if(strcmp(r->fields.stringval,"\\n") == 0)
			printf("\n");
		else if(strcmp(r->fields.stringval,"\\") == 0)
			printf("\\");
		else				
			printf("%s",r->fields.stringval);
	}
	else if(r->kind == BOOL_NK)
	{
		if(r->extra == BOOL_TRUE)
			printf("TRUE");
		else
			printf("FALSE");
	}
	else
		printf("Not a int/char/bool type, cannot print\n");
}

/* This is the Perform Action function, it perform the specified action or return an errorNode
	if the action conditions are not met. Only works on ACTION NODES, PRINTLIST, PRINT, PRODUCE
	READINT, and READCHAR actions.  All other node types result in an error. */

AST performAction(AST t)
{
	AST s = t;
	if(s->kind == ACTION_NK)
	{
		AST x = performAction(s->fields.subtrees.s1);
		AST y = applyNode(s->fields.subtrees.s2,x);
		displayAST(y);			
		return performAction(simplify(y));
	}
	if(s->kind == BASIC_FUNC_NK)
	{
		if(s->extra == PRILST_FK)
		{
			AST x= simplify(s->fields.subtrees.s1);
			while(x->kind != EMPTYLIST)
			{	
				if(x->kind == ERROR_NK)
					return errorNode(x->fields.stringval);
				AST y = applyBasicFunc(x,"head");
				printValue(simplify(y));
				y = applyBasicFunc(x,"tail");
				x = simplify(y);
			}
			return emptyList();
		}
		else if(s->extra == PRINT_FK)
		{
			AST r = simplify(s->fields.subtrees.s1);
			printValue(r);
			return emptyList();
		}
		else if(s->extra == PROD_FK)
		{
			return simplify(s->fields.subtrees.s1);
		}
		else if(s->extra == READI_FK)
		{
			char str[11];
			if(fgets(str,11,stdin) != NULL)		
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

/* This is the main interpreter function, if the tree(R) obtained by simplifying tree M is an action type
then performAction is called with tree R as the argument.  If the return value is not an empty list the result is 
displayed.  If tree R is not an action type then the tree is displayed.  Once the interpreter has run without error
a 0 is returned, otherwise if an error is encountered the error type is displayed and a 1 is returned. */

int runInterpreter(void)
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
			printf("Error: %s\n",ret->fields.stringval);
			return 1;
		}
		else if(ret->kind != EMPTYLIST)
		{
			displayAST(ret);
		}
	} 
	else
	{
		displayAST(R);
	}
	printf("\n");
	return 0;
}
