/*

	Name: Adrian J. Paparelli
	Class: CSCI 5220
	Session: Spring 2016

	Description: lexer.h contains variable definitiosn for use by the lexical analyzer
	in the absence of Bison.

	Change Log:
	2016-02-08: Initial Revision

*/

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

int yylex();

extern FILE* yyin;

YYSTYPE yylval;

int linenum;


#endif
