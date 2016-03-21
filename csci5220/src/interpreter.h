#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "ast.h"


void printChar(AST r);

int interpreter(void);

AST performAction(AST t);

#endif
