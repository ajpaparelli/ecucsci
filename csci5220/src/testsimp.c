#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symboltable.h"
#include "simplify.h"

int main() 
{
/*	AST a = applyParam(1);
	AST b = applyParam(2);
	AST c = applyOp(a,b,"*");
	AST d = applyFunction(c,2);
	AST e = applyFunction(d,1);
	AST f = numberNode(2);
	AST g = numberNode(3);
	AST h = applyNode(e,f);
	AST i = applyNode(h,g);
	displayAST(i);
	printf("\n\n");
	displayAST(simplify(i));
	printf("\n\n");
	displayAST(i);*/

/*	AST fn1 = numberNode(14);
	AST fn2 = numberNode(7);
	AST fn3 = applyOp(fn1,fn2,"-");
	
	AST fn6 = numberNode(69);
	AST fn7 = numberNode(0);
	AST fn8 = applyOp(fn6,fn7,"+");
	displayAST(simplify(fn8));
	
	printf("\n\n");
	
	AST fn9 = numberNode(10);
	AST fn10 = numberNode(3);
	AST fn11 = applyOp(fn9,fn10,"-");
	AST fn12 = emptyList();
	AST fn13 = applyCOLON(fn11,fn12);
	AST fn14 = numberNode(5);
	AST fn15 = applyCOLON(fn14,fn13);
	AST fn15a = applyCOLON(fn3,fn8);
	AST fn16 = applyCOLON(fn15a,fn15);
	
	AST fn17 = applyBasicFunc(fn16, "head");
	//displayAST(fn17);
	
	displayAST(fn16);
	
	printf("\n\n");
	
	displayAST(simplify(fn16));
	
	printf("\n\n");
	
	displayAST(simplify(fn17));
	
	
	AST a = numberNode(50);
	insertTree("fox",a);
	
	AST b = numberNode(51);
	insertTree("hound",b);
	
	AST c = idNode("fox");
	AST d = idNode("hound");
	AST e = applyOp(c,d,"+");
	displayAST(e);
	printf("\n\n");
	
	displayAST(simplify(e));*/
	
	
 	AST a = applyParam(1);
	AST b = applyParam(2);
	AST c = applyParam(3);
	AST d = applyOp(a,b,"*");
	AST e = applyOp(d,c,"+");
	AST f = applyFunction(e,3);
	AST g = applyFunction(f,2);
	AST h = applyFunction(g,1);
	insertTree("slope",h);
	
	AST i = idNode("slope");
	displayAST(simplify(i));
	printf("\n\n");
	
	AST tmp = numberNode(4);
	insertTree("m",tmp);
	tmp = numberNode(5);
	insertTree("x",tmp);
	tmp = numberNode(6);
	insertTree("b",tmp);
	
	AST id0 = idNode("m");
	AST id1 = idNode("x");
	AST id2 = idNode("b");
	
	AST ap0 = applyNode(i,id0);
	AST ap1 = applyNode(ap0,id1);
	AST ap2 = applyNode(ap1,id2);
	displayAST(ap2);
	printf("\n\n");
	displayAST(simplify(ap2));
	printf("\n\n");
	displayAST(ap2);
return 0;
}
