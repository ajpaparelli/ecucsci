%{
#include "lexer.h"
#include "token.h"
#include "stringtable.h"

YYSTYPE yylval;         /* This variable holds the token attribute */
%}

letter  [a-zA-Z]
digit   [0-9]
id      {letter}+
number  {digit}+

%%
[ \t]* 		{}
"\n" 		{line_number++;}
"("     	{return '(';}
")"		{return ')';}
"+"		{return '+';}
"-"		{return	'-';}
"*"		{return '*';}
"/"		{return '/';}
"<"		{return '<';}
">"		{return '>';}
"|"		{return '|';}
"&"		{return '&';}
";"		{return ';';}
":"		{return ':';}
","		{return ',';}
"["		{return '[';}
"]"		{return ']';}
"{"		{return '{';}
"}"		{return '}';}
"->"		{return TOK_ARROW;}
"~>"		{return TOK_ACTION;}
"=="		{return TOK_EQUIV;}
and		{return TOK_AND;}
case		{return TOK_CASE;}
def     	{return TOK_DEF;}
else		{return TOK_ELSE;}
end		{return TOK_END;}
false		{return TOK_FALSE;}
head		{return TOK_HEAD;}
in		{return TOK_IN;}
isBool		{return TOK_ISBOOL;}
isFunction	{return TOK_ISFUNC;}
isInt		{return TOK_ISINT;}
isList		{return TOK_ISLIST;}
isNull		{return TOK_ISNULL;}
let		{return TOK_LET;}
not		{return TOK_NOT;}
or		{return TOK_OR;}
print		{return TOK_PRINT;}
printList	{return TOK_PLIST;}
produce		{return TOK_PROD:
readChar	{return TOK_READC;}
readInt		{return TOK_READI;}
tail		{return TOK_TAIL;}
true		{return TOK_TRUE;}
"'"		{return TOK_QUOTE;}

{id}    	{yylval.str = intern(yytext);  /* Flex stores the lexeme into yytext. */
	         return TOK_ID;
        	}
{number}	{yyval.str = intern(yytext);
		 return TOK_NUM;
		}

"//"+{id}	{}
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
