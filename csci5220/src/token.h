#ifndef TOKEN_H
#define TOKEN_H
#define YYSTYPE_DEFINED
typedef union {
  char* str;
  int   ival;
} 
YYSTYPE;

#endif
