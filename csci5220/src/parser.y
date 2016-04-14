/*

	Name: Adrian J. Paparelli
	Class: CSCI 5220
	Session: Spring 2016

	Description: parser.y defines the grammar rules for the SFL language.

	Change Log:
	2016-04-05: Initial Revision

*/
%{
#include <stdio.h>
#include "token.h"
#include "lexer.h"
#include "interpreter.h"
#include "symboltable.h"
#define YYDEBUG 1
void installDefintions(AST lhs, AST body);
void yyerror(char const *s);
int error_occured;
int funcNum;
%}

%token TOK_ARROW
%token TOK_ACTION
%token <str> TOK_BOOL
%token <str> TOK_MULOP
%token <str> TOK_ADDOP
%token <str> TOK_RELOP
%token TOK_DEF
%token TOK_END
%token TOK_LET
%token TOK_IN
%token <str> TOK_LIST_FUNC
%token <str> TOK_ACTION_FUNC
%token <str> TOK_CHECK_FUNC
%token TOK_ELSE
%token TOK_CASE
%token <str> TOK_NOT
%token <str> TOK_LOGIC
%token <str> TOK_ID
%token <ival> TOK_INTEGER
%token TOK_THEN
%token <str> TOK_CHARCONST
%token <str> TOK_READ;
%token TOK_SEMI
%token TOK_COLON

%nonassoc TOK_ID TOK_INTEGER TOK_CHARCONST TOK_BOOL '[' '(' 
%nonassoc TOK_CHECK_FUNC TOK_LIST_FUNC TOK_ACTION_FUNC
%nonassoc TOK_RELOP TOK_LET TOK_CASE TOK_READ

%left TOK_MULOP
%left TOK_ADDOP
%left TOK_LOGIC
%left TOK_NOT
%left JUXT
%left TOK_SEMI
%left TOK_ACTION
%right TOK_ARROW
%right TOK_COLON

%type <tree> Expr
%type <tree> IdList
%type <tree> Id
%type <tree> List
%type <tree> ExprList

%%
Program		: 
		| Definitions
			{}		
		;

Definitions	: Definition
			{}
		| Definitions Definition
			{}
		;

Definition	: TOK_DEF IdList '=' Expr TOK_END
			{  
				installDefintions($2, $4);
			}
		| error TOK_END
		;

Expr		: Id
			{
				$$ = $1;
			}
		| TOK_INTEGER
			{
				$$ = numberNode($1);
			}
		| TOK_CHARCONST
			{
				$$ = charNode($1);
			}	
		| TOK_BOOL
			{
				$$ = boolNode($1);
			}
		| List
			{
				$$ = $1;
			}
		| '(' Expr ')'
			{
				$$ = $2;
			}
		| Expr Expr %prec JUXT
			{
				$$ = applyNode($1,$2);
			}
		| Expr TOK_ACTION Expr
			{
				$$ = applyAction($1,$3);
			}
		| Expr TOK_SEMI Expr
			{
				$$ = applyCONS($1,$3);
			}
		| Expr TOK_ARROW Expr
			{
				
			}
		| Expr TOK_MULOP Expr
			{
				$$ = applyOp($1,$3,$2);
			}
		| Expr TOK_ADDOP Expr
			{
				$$ = applyOp($1,$3,$2);
			}
		| Expr TOK_LOGIC Expr
			{
				$$ = applyOp($1,$3,$2);
			}
		| Expr TOK_RELOP Expr
			{
				$$ = applyOp($1,$3,$2);
			}
		| Expr TOK_COLON Expr
			{
				$$ = applyCOLON($1,$3);
			}
		| TOK_NOT Expr
			{
				$$ = applyOp($2,NULL,$1);
			}
		| TOK_LIST_FUNC Expr
			{
				$$ = applyBasicFunc($2, $1);
			}
		| TOK_CHECK_FUNC Expr
			{
				$$ = applyBasicFunc($2, $1);
			}
		| TOK_ACTION_FUNC Expr
			{
				$$ = applyBasicFunc($2, $1);
			}
		| TOK_READ
			{
				$$ = applyBasicFunc(emptyList(),$1);
			}
		| TOK_CASE CaseList '|' TOK_ELSE TOK_THEN Expr TOK_END
		| TOK_LET Id '=' Expr TOK_IN Expr TOK_END
			{
				insertTree($2->fields.stringval, $4);
				$$ = $6;
			}
		;


List		: '[' ']'
			{
				$$ = emptyList();
			}
		| '[' ExprList ']'
			{
				$$ = $2;
			}
		;

ExprList	: Expr
			{
				$$ = applyCONS($1, emptyList());
			}
		| Expr ',' ExprList
			{
				$$ = applyCONS($1,$3);
			}
		;

IdList		: 
			{
				$$ = emptyList();
			}
		| IdList Id
			{
				$$ = applyCONS($2,$1);
			}
		;

Id		: TOK_ID
			{
				$$ = idNode($1);
			}

CaseList	: Case
		| CaseList '|' Case
		;

Case		: Expr TOK_THEN Expr
		;

%%
void installDefintions(AST lhs, AST body)
{
	AST nb = body;
	AST defnode = lhs->fields.subtrees.s1;
		
	/*for(AST p = lhs->fields.subtrees.s1; p->next != NULL; p = p->next)
	{
		nb = applyFunction(nb, funcNum, nb->name);
		funcNum++;	
	}*/
	
	insertTree(defnode->fields.stringval, nb);
}

int main(int argc, char** argv)
{
	linenum = 0;
	funcNum = 0;
	error_occured = 0;
	if(argc == 2) 
	{
		yyin = fopen(argv[1],"r");
		if(yyin == NULL)
			return 1;
		yydebug = 0;
		yyparse();
		if(!error_occured)
		{			
			return runInterpreter();
		}
	}
	else
		return 1;
}

void yyerror(char const *s)
{
	printf("Syntax Error on line : %d \n",linenum);
	error_occured = 1;
}

