#ifndef GC_H_
#define GC_H_
#include "ast.h"

#define AST_MEM_SIZE 1000

void initialize_gc(void);

AST getNewAST(void);

int garbageCollect(void);






#endif
