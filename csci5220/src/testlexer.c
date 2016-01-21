#include "lexer.h"

/*========================================================*
 * This main function tests the lexer function, yylex().  *
 * It assumes that the command line contains the name of  *
 * a file to read.                                        *
 *========================================================*/

int main(int argc, char *argv[])
{
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
      else {
        printf("Token %d\n",yylval.ival);
      }
    }
  }
	return 0;
}
