#ifndef TOKEN_H
#define TOKEN_H
#define YYSTYPE_DEFINED
typedef union {
  char* str;
  int   ival;
} 
YYSTYPE;

#define TOK_ARROW 255
#define TOK_PROD 256
#define TOK_DEF 257
#define TOK_END 258
#define TOK_LET 259
#define TOK_TAIL 260
#define TOK_HEAD 261
#define TOK_ACTION 262
#define TOK_CHECK 263
#define TOK_IFOP 264
#define TOK_LOGIC 265
#define TOK_BOOL 266
#define TOK_MULOP 267
#define TOK_ADDOP 268
#define TOK_RELOP 269
#define TOK_ID 270
#define TOK_INTEGER 271
#define TOK_IN 272
#endif
