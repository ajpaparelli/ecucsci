#include <stdio.h>
#include "ast.h"
#include "symboltable.h"

int main()
{

AST fn1 = applyParam(1);
AST fn2 = applyParam(1);
AST fn3 = applyOp(fn1, fn2, "+");
AST fn4 = applyFunction(fn3, 1);
/*if(hasFunc("test") == 1) 
	printf("How did that get there?\n");*/

insertTree("test",fn4);
insertTree("main",fn4);
displayContents();
insertTree("slope",fn4);
displayContents();
insertTree("jupiter",fn4);
insertTree("mars",fn4);
insertTree("apple",fn4);
displayContents();
insertTree("banana",fn3);
displayContents();

if(hasFunc("test") == 1) 
{
	AST A = getTree("test");
	
	displayAST(A);
}

if(hasFunc("apple") == 1) 
{
	printf("Found apple\n");
	AST A = getTree("apple");
	
	displayAST(A);
}

if(hasFunc("mars") == 1) 
{
	printf("Found mars\n");

	AST A = getTree("mars");
	
	displayAST(A);
}

if(hasFunc("banana") == 1) 
{
	printf("Found banana\n");

	AST A = getTree("banana");
	
	displayAST(A);
}


return 0;
}
