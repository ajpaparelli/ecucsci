#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_
#include <stdio.h>
#include "allocate.h"
#include "ast.h"

#define TABLE_SIZE 2

typedef struct hashnode {
	char* funcName;
	AST astTree;
	struct hashnode* next;
} HASHNODE;

typedef HASHNODE* HASH;


int hashify(char* key);

int hasFunc(char* key);

void displayContents();

AST getTree(char* key);

void insertTree(char* key, AST A);

#endif
