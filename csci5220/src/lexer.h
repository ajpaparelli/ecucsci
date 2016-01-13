#include <stdio.h>

int yylex();

extern FILE* yyin;
YYSTYPE yyval;

#define TOK_ARROW 256
#define TOK_ACTION 257
#define TOK_EQUIV 258
//#define TOK_COMMENT 259
#define TOK_AND 260
#define TOK_CASE 261
#define TOK_DEF 262
#define TOK_ELSE 263
#define TOK_END 264
#define TOK_FALSE 265
#define TOK_HEAD 266
#define TOK_IN 267
#define TOK_ISBOOL 268
#define TOK_ISFUNC 269
#define TOK_ISINT 270
#define TOK_ISLIST 271
#define TOK_ISNULL 272
#define TOK_LET 273
#define TOK_NO 274
#define TOK_OR 275
#define TOK_PRINT 276
#define TOK_PLIST 277
#define TOK_PROD 278
#define TOK_READC 279
#define TOK_READI 280
#define TOK_TAIL 281
#define TOK_TRUE 282
#define TOK_QUOTE 283
#define TOK_ID 284
#define TOK_NUM 285


