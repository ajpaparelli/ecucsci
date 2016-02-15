#include <stdio.h>
#include "ast.h"

int main() 
{
	
	AST fn1 = numberNode(5);
	AST fn2 = numberNode(4);
	AST fn3 = applyOp(fn1,fn2,'+');
	AST fn4 = numberNode(6);
	AST fn5 = applyOp(fn3,fn4,'*');
	displayAST(fn5);
		return 0;
}
