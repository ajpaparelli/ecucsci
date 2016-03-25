#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symboltable.h"
#include "simplify.h"
#include "interpreter.h"

AST setupList(const char* str,int x)
{
	if(x == strlen(str))
	{
		AST tmp = NEW(ASTNODE);
		tmp->kind = COLON_NK;
		tmp->fields.subtrees.s1 = charNode("\n");
		tmp->fields.subtrees.s2 = emptyList();
		return tmp;
	}
	else
	{
		AST tmp = NEW(ASTNODE);	
		char tmpstr[2];
		memcpy(tmpstr,&str[x],1);
		tmpstr[1] = '\0';
		tmp->kind = COLON_NK;
		tmp->fields.subtrees.s1 = charNode(tmpstr);
		tmp->fields.subtrees.s2 = setupList(str,x+1);
		return tmp;
	}	
}


int main() 
{
	AST s = setupList("How many seconds?",0);
	//displayAST(s);
	//displayAST(simplify(s));
	
	AST BF0 = applyBasicFunc(s,"printList");
	AST BF1 = applyBasicFunc(emptyList(),"readInt");
	AST F1 = applyFunction(BF1,1,"");
	AST ACT1 = applyAction(BF0,F1);
	
	AST a1 = idNode("n");
	AST a2 = numberNode(60);
	AST a3 = applyOp(a1,a2,"/");
	//displayAST(a3);
	insertTree("m",a3);

	AST b1 = idNode("n");
	AST b2 = numberNode(3600);
	AST b3 = applyOp(b1,b2,"/");
	//displayAST(b3);
	insertTree("h",b3);

	AST c1 = numberNode(60);
	AST c2 = idNode("m");
	AST c3 = applyOp(c1,c2,"*");
	AST c4 = idNode("n");
	AST c5 = applyOp(c4,c3,"-");
	//displayAST(c5);
	insertTree("secs",c5);
	
	AST d1 = numberNode(60);
	AST d2 = idNode("h");
	AST d3 = applyOp(d1,d2,"*");
	AST d4 = idNode("m");
	AST d5 = applyOp(d4,d3,"-");
	//displayAST(d5);
	insertTree("mins",d5);

	AST h1 = numberNode(5);
	AST h2 = numberNode(0);
	AST h3 = applyOp(h1,h2,"/");
	insertTree("test",h3);
	AST _t = idNode("test");

	AST _mins = idNode("mins");
	AST _secs = idNode("secs");
	AST _h = idNode("h");
	
	AST l1a = applyCOLON(charNode("\n"),emptyList());	
	AST l0 = applyCOLON(_secs,l1a);
	AST l1 = applyCOLON(charNode(":"),l0);
	AST l2 = applyCOLON(_mins,l1);
	AST l3 = applyCOLON(charNode(":"),l2);
	AST l4 = applyCOLON(_h,l3);
	AST l5 = applyCOLON(charNode(":"),l4);
	AST l6 = applyCOLON(_t,emptyList());
	AST BF2 = applyBasicFunc(l6,"printList");	
	AST F6 = applyFunction(BF2,6,"mins");
	AST APP4 = applyNode(F6,d5);
	//displayAST(APP4);
	AST F5 = applyFunction(APP4,5,"secs");
	AST APP3 = applyNode(F5,c5);
	//displayAST(APP3);
	AST F4 = applyFunction(APP3,4,"h");
	AST APP2 = applyNode(F4,b3);
	//displayAST(APP2);
	AST F3 = applyFunction(APP2,3,"m");
	AST APP1 = applyNode(F3,a3);
	//displayAST(APP1);
	//displayAST(simplify(APP1));
	AST F2 = applyFunction(APP1,2,"n");
	//displayAST(F2);
	AST ACT2 = applyAction(ACT1,F2);
	//displayAST(ACT2);
	insertTree("main",ACT2);
//	displayAST(simplify(idNode("main")));
	//int x = interpreter();
	displayAST(simplify(l6));	

	
//	insertTree("main",a);
	
//	int x = interpreter();
//	printf("\n%d\n",x);
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
	
	AST fn17 = applyBasicFunc(fn16, "tail");
	
	displayAST(fn17);
	
	//displayAST(fn16);
	
	printf("\n\n");
	//displayAST(simplify(fn16));
	
	printf("\n\n");
	
	displayAST(simplify(fn17));*/
	
	
	/*AST a = numberNode(50);
	insertTree("fox",a);
	
	AST b = numberNode(51);
	insertTree("hound",b);
	
	AST c = idNode("fox");
	AST d = idNode("hound");
	AST e = applyOp(c,d,"+");
	displayAST(e);
	printf("\n\n");
	
	displayAST(simplify(e));*/
	
	
 	/*AST a = applyParam(1);
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
	displayAST(ap2);*/

/*	AST a = numberNode(5);
	AST a1 = numberNode(25);
	AST a2 = applyOp(a,a1,"*");
	AST b = applyBasicFunc(a2,"print");*/

/*	AST a = charNode("H");
	AST b = charNode("e");
	AST c = charNode("l");
	AST d = charNode("l");
	AST e = charNode("o");
	AST f = charNode("!");
	AST g = charNode("\n");
	
	AST h1 = emptyList();
	AST g1 = applyCOLON(g,h1);
	AST f1 = applyCOLON(f,g1);
	AST e1 = applyCOLON(e,f1);
	AST d1 = applyCOLON(d,e1);
	AST c1 = applyCOLON(c,d1);
	AST b1 = applyCOLON(b,c1);
	AST a1 = applyCOLON(a,b1);

	AST x = applyBasicFunc(a1,"printList");
	AST y = performAction(x);
	displayAST(simplify(y));*/
return 0;
}
