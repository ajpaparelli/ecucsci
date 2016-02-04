#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"
int yylex();

extern FILE* yyin;
YYSTYPE yylval;


#endif
