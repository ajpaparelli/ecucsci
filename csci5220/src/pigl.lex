%{
#include "token.h"
#include "lexer.h"
#include "string.h"
#include "stringtable.h"

YYSTYPE yylval;
%}

letter  [a-zA-Z]
vowel	[a|e|i|o|u|A|E|I|O|U]

%%
[^{letter}] 		{printf("%c",yytext[0]);}
{vowel}({letter})* 	{printf("%say",yytext);}
({letter})* 		{	
						int i;
		       			int len = strlen(yytext);
		       			for(i = 1; i < len; i++)
							printf("%c",yytext[i]);

						printf("%c",yytext[0]);
			      		printf("ay");
		  			}
<<EOF>>			    { yyterminate(); }
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
  	if(argc == 2)
	{
    	yyin = fopen(argv[1], "r");
    	
		if(yyin == NULL)
			return 1;
	}
	else
		yyin = stdin;

    yylex();
	return 0;
}
