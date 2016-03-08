#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "ast.h"
#include "simplify.h"


void printChar(AST r);

AST performAction(AST t);

#endif
