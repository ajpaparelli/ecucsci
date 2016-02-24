#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int main() 
{
	
	AST i = numberNode(10);
	AST y = NULL;
	displayAST(i);
	printf("\n\n");
	free(i);

	i = idNode("Apple");
	displayAST(i);
	printf("\n\n");
	free(i);
	
	i = boolNode("true");
	displayAST(i);
	printf("\n\n");
	free(i);

	i = boolNode("false");
	displayAST(i);
	printf("\n\n");
	free(i);

	i = applyParam(30);
	displayAST(i);
	printf("\n\n");
	free(i);

	i = emptyList();
	displayAST(i);
	printf("\n\n");
	free(i);

	AST fn1 = numberNode(5);
	AST fn2 = numberNode(4);
	AST fn3 = applyOp(fn1,fn2,"+");
	AST fn4 = numberNode(6);
	AST fn5 = applyOp(fn3,fn4,"*");
	displayAST(fn5);
	printf("\n\n");

	AST fn6 = numberNode(1);
	AST fn7 = numberNode(2);
	AST fn8 = applyOp(fn6,fn7,"+");


	AST fn9 = numberNode(10);
	AST fn10 = numberNode(3);
	AST fn11 = applyOp(fn9,fn10,"-");
	AST fn12 = emptyList();
	AST fn13 = applyCONS(fn11,fn12);
	AST fn14 = numberNode(5);
	AST fn15 = applyCONS(fn14,fn13);
	AST fn16 = applyCONS(fn8,fn15);
	displayAST(fn16);

	printf("\n\n");
	AST fn17 = boolNode("true");
	AST fn18 = boolNode("false");
	AST fn19 = applyOp(fn17,fn18,"and");
	displayAST(fn19);

	printf("\n\n");
	AST fn20 = idNode("Apple");
	AST fn21 = applyBasicFunc(fn20, "isNull");
	displayAST(fn21);

	printf("\n\n");
	AST fn22 = idNode("Banana");
	AST fn23 = idNode("Waffle");
	AST fn24 = applyProd(fn22, fn23);
	displayAST(fn24);
		

	printf("\n\n");
	AST fn25 = idNode("A");
	AST fn26 = numberNode(9);
	AST fn27 = applyOp(fn25,fn26,"<");

	AST fn28 = idNode("Carrot");
	AST fn29 = applyBasicFunc(fn28,"print");

	AST fn30 = idNode("A");
	AST fn31 = numberNode(15);
	AST fn32 = applyOp(fn30,fn31,"<");

	AST fn33 = idNode("Juice");
	AST fn34 = applyBasicFunc(fn33,"print");

	AST fn35 = idNode("A");
	AST fn36 = numberNode(30);
	AST fn37 = applyOp(fn35,fn36,"<");

	AST fn38 = idNode("Slushie");
	AST fn39 = applyBasicFunc(fn38,"print");

	AST fn40 = idNode("Drink");
	AST fn41 = applyBasicFunc(fn40,"print");
	AST fn43 = applyBranch(fn37, fn39, fn41);
	AST fn44 = applyBranch(fn32, fn34, fn43);
	AST fn45 = applyBranch(fn27, fn29, fn44);
	displayAST(fn45);

	printf("\n\n");
	AST fn46 = applyParam(1);
	AST fn47 = applyParam(2);
	AST fn48 = applyParam(3);
	AST fn49 = applyOp(fn46,fn47,"*");
	AST fn50 = applyOp(fn49,fn48,"+");
	AST fn51 = applyFunction(fn50,3);
	AST fn52 = applyFunction(fn51,2);
	AST fn53 = applyFunction(fn52,1);
	displayAST(fn53);


	displayAST(y);

return 0;
}
