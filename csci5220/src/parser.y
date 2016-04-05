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
#define YYDEBUG 1
void yyerror(char const *s);
int error_occured;
%}

%token TOK_ARROW
%token TOK_PROD
%token TOK_BOOL
%token TOK_MULOP
%token TOK_ADDOP
%token TOK_RELOP
%token TOK_DEF
%token TOK_END
%token TOK_LET
%token TOK_IN
%token TOK_LIST_FUNC
%token TOK_ACTION_FUNC
%token TOK_CHECK_FUNC
%token TOK_ELSE
%token TOK_CASE
%token TOK_NOT
%token TOK_LOGIC
%token TOK_ID
%token TOK_INTEGER
%token TOK_THEN
%token TOK_CHARCONST
%token TOK_SEMI
%token TOK_COLON

%nonassoc TOK_ID TOK_INTEGER TOK_CHARCONST TOK_BOOL '[' '(' 
%nonassoc TOK_CHECK_FUNC TOK_LIST_FUNC TOK_ACTION_FUNC
%nonassoc TOK_RELOP TOK_LET TOK_CASE
%left TOK_MULOP
%left TOK_ADDOP
%left TOK_LOGIC
%left TOK_NOT
%left JUXT
%left TOK_SEMI
%left TOK_PROD
%right TOK_ARROW
%right TOK_COLON

%%
Program		: 
		| Definitions		
		;

Definitions	: Definition
		| Definitions Definition
		;

Definition	: TOK_DEF IdList '=' Expr TOK_END
		| error TOK_END
		;

Expr		: Id
		| TOK_INTEGER
		| TOK_CHARCONST
		| TOK_BOOL
		| List
		| '(' Expr ')'
		| Expr Expr %prec JUXT
		| Expr TOK_PROD Expr
		| Expr TOK_SEMI Expr
		| Expr TOK_ARROW Expr
		| Expr TOK_MULOP Expr
		| Expr TOK_ADDOP Expr
		| Expr TOK_LOGIC Expr
		| Expr TOK_RELOP Expr
		| Expr TOK_COLON Expr
		| TOK_NOT Expr
		| TOK_LIST_FUNC Expr
		| TOK_CHECK_FUNC Expr
		| TOK_ACTION_FUNC
		| TOK_CASE CaseList '|' TOK_ELSE TOK_THEN Expr TOK_END
		| TOK_LET TOK_ID '=' Expr TOK_IN Expr TOK_END
		;


List		: '[' ']'
		| '[' ExprList ']'
		;

ExprList	: Expr
		| Expr ',' ExprList
		;

IdList		: 
		| IdList Id
		;

Id		: TOK_ID
		;

CaseList	: Case
		| CaseList '|' Case
		;

Case		: Expr TOK_THEN Expr
		;

%%
int main(int argc, char** argv)
{
	linenum = 0;
	error_occured = 0;
	if(argc == 2) 
	{
		yyin = fopen(argv[1],"r");
		if(yyin == NULL)
			return 1;
		yydebug = 1;
		return yyparse();
	}
	else
		return 1;
}

void yyerror(char const *s)
{
	printf("Syntax Error on line : %d \n",linenum);
	error_occured = 1;
}
