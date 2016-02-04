%{
#include "token.h"
#include "lexer.h"
#include "stringtable.h"

YYSTYPE yylval;
%}

ws  [ \t]


%%

{ws}+	{printf(" ");}
(^{ws})	{printf("%s",yytext);}
<<EOF>> { yyterminate(); }
%%

/*======================================================*
 * yylex calls yywrap() when it encounters the end of   *
 * the file.  Returned value 1 tells yylex to return 0, *
 * which is yylex's way of saying 'end of file'.        *
 *======================================================*/

int yywrap()
{
  return 1;
}

int main(int argc, char *argv[])
{
  if(argc == 2) {
    /*----------------------------------*
     * Flex reads from open file yyin.  *
     *----------------------------------*/

    yyin = fopen(argv[1], "r");
	}

    /*---------------------------------------------*
     * yylex() reads a lexeme and returns a token. *
     *---------------------------------------------*/
	yylex();
	return 0;
}
