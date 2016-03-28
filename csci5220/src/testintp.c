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
	AST s = setupList("Input secret character...",0);
	
	AST BF0 = applyBasicFunc(s,"printList");
	AST BF1 = applyBasicFunc(emptyList(),"readChar");
	AST F1 = applyFunction(BF1,1,"");
	AST ACT1 = applyAction(BF0,F1);
	
	AST OP1 = boolNode("true");
	AST OP2 = boolNode("true");
	AST OP3 = applyOp(OP1, OP2, "and");
	AST OP4 = applyOp(OP3, NULL, "not");

	AST a1 = numberNode(1000);
	AST a2 = applyBasicFunc(OP4,"print");
	insertTree("y",a2);

	AST b1 = boolNode("false");
	AST b2 = applyBasicFunc(b1,"print");
	insertTree("n",b2);

	
/*	AST IF1 = idNode("sc");
	AST IF2 = charNode("X");
	AST IF3 = applyOp(IF1,IF2,"==");
	AST IF4 = applyBranch(IF3, a2, b2);
	AST F2 = applyFunction(IF4,2,"sc");
	AST ACT2 = applyAction(ACT1,F2);*/
	insertTree("main",idNode("y"));
/*	AST s = setupList("How many seconds?",0);
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
	AST BF2 = applyBasicFunc(l4,"printList");	
	AST F6 = applyFunction(BF2,6,"mins");
	AST APP4 = applyNode(F6,d5);
	AST F5 = applyFunction(APP4,5,"secs");
	AST APP3 = applyNode(F5,c5);
	AST F4 = applyFunction(APP3,4,"h");
	AST APP2 = applyNode(F4,b3);
	AST F3 = applyFunction(APP2,3,"m");
	AST APP1 = applyNode(F3,a3);
	AST F2 = applyFunction(APP1,2,"n");
	AST ACT2 = applyAction(ACT1,F2);
	insertTree("main",ACT2);*/
	int x = runInterpreter();	

	printf("\n%d\n",x);	

return 0;
}
