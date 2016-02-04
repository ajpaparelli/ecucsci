%{
#include "token.h"
#include "lexer.h"
#include "string.h"
#include "stringtable.h"

YYSTYPE yylval;
int linenum = 0;
%}

letter  [a-zA-Z]
digit   [0-9]
id      {letter}+
number  {digit}+
comment "//".*\n

%%

[ \t] 		{}
comment		{}
"\n" 		{linenum++;}
"("     	{return '(';}
")"		{return ')';}
";"		{return ';';}
":"		{return ':';}
","		{return ',';}
"["		{return '[';}
"]"		{return ']';}
"|"		{return '|';}
"="		{return '=';}
"->"		{return TOK_ARROW;}
"~>"		{return TOK_PROD;}
def     	{yylval.str = yytext;
		 return TOK_DEF;}
end		{yylval.str = yytext;
		 return TOK_END;}
let		{yylval.str = yytext;
		 return TOK_LET;}
tail		{yylval.str = yytext;
		 return TOK_TAIL;}
in		{yylval.str = yytext;
		 return TOK_IN;}
head|isList|isNull	{yylval.str = yytext;
		 	 return TOK_HEAD;
			}	
print|printList|produce|readChar|readInt {yylval.str = yytext;
		 			  return TOK_ACTION;
					 }
isBool|isFunction|isInt|isAction	{yylval.str = yytext;
		 		 	 return TOK_CHECK;
					}
case|if|else	{yylval.str = yytext;
		 return TOK_IFOP;
		}
and|or|not	{yylval.str = yytext;
		 return TOK_LOGIC;
	        }
true|false      {yylval.str = yytext;
		 return TOK_BOOL;
		}
"*"|"/"		{yylval.str = yytext;
		 return TOK_MULOP;
		}
"+"|"-"		{yylval.str = yytext;
		 return TOK_ADDOP;
		}
"=="|">"|"<"	{yylval.str = yytext;
		 return TOK_RELOP;
		}
{id}    	{yylval.str = intern(yytext);
	         return TOK_ID;
        	}
{number}	{yylval.ival = atoi(yytext);
		 return TOK_INTEGER;
		}
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
