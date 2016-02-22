#include "lexer.h"

/*========================================================*
 * This main function tests the lexer function, yylex().  *
 * It assumes that the command line contains the name of  *
 * a file to read.                                        *
 *========================================================*/

int main(int argc, char *argv[])
{
	linenum = 0;
  if(argc == 2) {
    /*----------------------------------*
     * Flex reads from open file yyin.  *
     *----------------------------------*/

    yyin = fopen(argv[1], "r");
    if(yyin == NULL) return 1;

    /*---------------------------------------------*
     * yylex() reads a lexeme and returns a token. *
     *---------------------------------------------*/

    while(1) {
      int tok = yylex();

      if(tok == 0) {
        break;
      }

      else if(tok == TOK_ID) {
        printf("ID, name = %s\n", yylval.str);
      }
      else if(tok == TOK_INTEGER) {
	printf("INTEGER, value = %d\n", yylval.ival);
      }
      else {
	printf("Token %d (\"%s\")\n", tok, yylval.str);
      }
    }
  }
	printf("Total lines: %d\n",linenum);
	return 0;
}
