%{
#define YYDEBUG
#include "token.h"
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

//%type <tree> Fact
//%type <tree> Term
//%type <tree> Expr
//%type <tree> Case
//%type <tree> List
//%type <t
%left LP
%right RP
%%
Program		: 
		| Definitions		
		;

Definitions	: Definition
		| Definitions Definition
		;

Definition	: TOK_DEF TOK_ID '=' Expr TOK_END
		;

Expr		: Term	
		| List
		| Boolean	
		| CharConst
		| TOK_ID
		| TOK_CASE CaseList TOK_ELSE Expr TOK_END
		| TOK_LET TOK_ID '=' Expr TOK_IN Expr TOK_END
		;

Boolean		: BoolFact
		| Boolean TOK_LOGIC BoolFact
		| TOK_NOT BoolFact
		;

BoolFact	: TOK_BOOL
		| '(' Boolean ')'
		;

CharConst	: TOK_CHARCONST
		;

Term		: Fact
		| Term TOK_ADDOP Fact %prec LP
		| Term TOK_MULOP Fact %prec LP
		;

Fact		: TOK_INTEGER
		| '(' Term ')'
		;

List		: '[' ']'
		| '[' ExprList ']'
		;

ExprList	: Expr
		| Expr ',' ExprList
		;

CaseList	: Case
		| CaseList '|' Case
		;

Case		: Expr TOK_THEN Expr
		;

%%
int main(int argc, char** argv)
{
	if(argc == 2) 
	{
		yyin = fopen(argv[1],"r");
		if(yyin == NULL
			return 1;
		
		yydebug = 1;
		return yyparse();
	}
	else
		return 1;
}
