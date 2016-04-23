#ifndef GC_H_
#define GC_H_
#include "ast.h"

#define AST_MEM_SIZE 10000

void initialize_gc(void);

AST getNewAST(void);

int garbageCollect(void);

void markALL(AST t);

#endif
