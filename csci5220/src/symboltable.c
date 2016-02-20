#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "ast.h"

HASHNODE* symTable[TABLE_SIZE];

int hashify(char* key)
{
	unsigned int hash = 0;
        int i;
	for(i = 0; key[i] != '\0'; i++)
	{
		hash = 31 * hash + key[i];
	}
	return hash % TABLE_SIZE;
}

int hasFunc(char* key)
{
	int index, hasKey;
	HASHNODE* hn;
	

	hasKey = -1;
	index = hashify(key);
	hn = symTable[index];
	while(hn != NULL)
	{
		if(strcmp(key,hn->funcName) == 0)
		{
			hasKey = 1;
			break;
		}
		else
			hn = hn->next;
	}
	return hasKey;
}

AST getTree(char* key)
{
	int index;
	HASHNODE* hn;
	AST tree;

	tree = NULL;
	index = hashify(key);
	hn = symTable[index];
	while(hn != NULL)
	{
		if(strcmp(key,hn->funcName) == 0)
		{
			tree = hn->astTree;
			break;
		}
		else
			hn = hn->next;
	}
	return tree;
}

void insertTree(char* key, AST A)
{
	int index;
	HASHNODE* hn;
	index = hashify(key);
	
	if(symTable[index] == NULL)
	{
		
		hn = NEW(HASHNODE);	
		hn->funcName = key;
		hn->astTree = A;
		hn->next = NULL;  
		symTable[index] = hn;
	}
	else
	{
		hn = symTable[index];
		while(hn->next != NULL)
			hn = hn->next;
		
		hn->next = NEW(HASHNODE);
		
		hn = hn->next;
		strcpy(hn->funcName,key);
		hn->astTree = A;
		hn->next = NULL;
	}		
}
