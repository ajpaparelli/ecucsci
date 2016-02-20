#include <stdio.h>
#include "ast.h"
#include "symboltable.h"

int main()
{

AST fn1 = applyParam(1);
AST fn2 = applyParam(1);
AST fn3 = applyOp(fn1, fn2, "+");
AST fn4 = applyFunction(fn3, 1);
if(hasFunc("test") == 1) 
	printf("How did that get there?\n");

if(hasFunc("test") != 1)
{
	insertTree("test",fn4);

}

if(hasFunc("test") == 1) 
{
	AST A = getTree("test");
	
	displayAST(A);
}




return 0;
}
