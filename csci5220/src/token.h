/*

	Name: Adrian J. Paparelli
	Class: CSCI 5220
	Session: Spring 2016

	Description: token.h contains all non-character token definitions
	for the Lexical Analyzer.

	Change Log:
	2016-02-08: Initial Revision

*/

#ifndef TOKEN_H
#define TOKEN_H
#define YYSTYPE_DEFINED

typedef union {
  const char* str;
  int   ival;
} 
YYSTYPE;

#define TOK_ARROW 256
#define TOK_PROD 257
#define TOK_BOOL 258
#define TOK_MULOP 259
#define TOK_ADDOP 260
#define TOK_RELOP 261
#define TOK_DEF 262
#define TOK_END 263
#define TOK_LET 264
#define TOK_IN 265
#define TOK_LIST_FUNC 266
#define TOK_ACTION_FUNC 267
#define TOK_CHECK_FUNC 268
#define TOK_CHECK 269
#define TOK_IFOP 270
#define TOK_LOGIC 271
#define TOK_ID 272
#define TOK_INTEGER 273
#define TOK_THEN 274
#define TOK_CHARCONST 275

#endif
