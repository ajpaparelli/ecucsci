#ifndef SIMPLIFY_H_
#define SIMPLIFY_H_

#include "ast.h"

AST getHead(AST t);

AST buildTail(AST t);

AST simplify(AST t);

AST copyTree(AST r, AST s, int x);

AST applyValue(AST r, AST s);

#endif
