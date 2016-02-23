/*

	Name: Adrian J. Paparelli
	Class: CSCI 5220
	Session: Spring 2016

	Description: lexer.lex contains all code to handle lexeme processing
	for the Lexical Analyzer.

	Change Log:
	2016-02-08: Initial Revision

*/

%{
#include "token.h"
#include "lexer.h"
#include "stringtable.h"

YYSTYPE yylval;
%}

%option noinput
%option nounput

letter  [a-zA-Z]
digit   [0-9]
id      {letter}+
number  {digit}+

%%

[ \t] 		{}


\'({letter}|\\\\|\\n)\' {yylval.str = intern(yytext);
		 return TOK_CHARCONST;
		}

"//".*\n|"\n"	{linenum++;
		}

"("|")"|";"|":"|","|"["|"]"|"|"|"=" { yylval.str = yytext;
		return yytext[0];
		}

"->"		{yylval.str = yytext;
		 return TOK_ARROW;
		}

"~>"		{yylval.str = yytext;
		 return TOK_PROD;
		}

"=>"		{yylval.str = yytext;
		 return TOK_THEN;
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



def     	{yylval.str = yytext;
		 return TOK_DEF;
		}

end		{yylval.str = yytext;
		 return TOK_END;
		}

let		{yylval.str = yytext;
		 return TOK_LET;
		}

in		{yylval.str = yytext;
		 return TOK_IN;
		}

head|tail	{yylval.str = yytext;
	 	 return TOK_LIST_FUNC;
		}	

print|printList|produce|readChar|readInt {yylval.str = yytext;
		 			  return TOK_ACTION_FUNC;
					 }

isList|isNull|isBool|isFunction|isInt|isAction	{yylval.str = yytext;
		 		 	 return TOK_CHECK_FUNC;
					}

case|if|else	{yylval.str = yytext;
		 return TOK_IFOP;
		}

and|or|not	{yylval.str = yytext;
		 return TOK_LOGIC;
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
