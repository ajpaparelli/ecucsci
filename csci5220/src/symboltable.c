#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "ast.h"

HASH* symTable;
int tableSize = TABLE_SIZE;
int prevSize = 0;
int items = 0;

int hashify(char* key)
{
	unsigned int hash = 0;
        int i;
	for(i = 0; key[i] != '\0'; i++)
	{
		hash = 31 * hash + key[i];
	}
	return hash % tableSize;
}

int hasFunc(char* key)
{
	int index, hasKey;
	HASH hn;
	

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
	HASH hn;
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

void displayContents()
{
	int i = 0;
	if(symTable != NULL)
	{
		for(i = 0; i < tableSize; i = i + 1)
		{
			HASH hn = symTable[i];
			while(hn != NULL)
			{
				printf("%d: %s\n",i, hn->funcName);
				hn = hn->next;
			}
		}
	}
}

void rehash()
{
	int i = 0;
	int index;
	tableSize = tableSize * 2;
	printf("Table approaching capacity need to rehash to size %d\n",tableSize);
	HASH hn;
	HASH* tmpTable = symTable;
	HASH* newTable = NEWARRAY(HASH, tableSize);

	for(i = 0; i < prevSize; i = i + 1)
	{
		HASH hnOLD = tmpTable[i];
		while(hnOLD != NULL)
		{
			index = hashify(hnOLD->funcName);
			if(newTable[index] == NULL)
			{				
				hn = NEW(HASHNODE);
				hn->funcName = hnOLD->funcName;
				hn->astTree = hnOLD->astTree;
				hn->next = NULL;	
				newTable[index] = hn;
			}
			else
			{
				hn = newTable[index];
				while(hn->next != NULL)
					hn = hn->next;
			
				hn->next = NEW(HASHNODE);
			
				hn = hn->next;
				hn->funcName = hnOLD->funcName;
				hn->astTree = hnOLD->astTree;
				hn->next = NULL;	
			} 
			hnOLD = hnOLD->next;
		}
	}
	
	symTable = newTable;
	free(tmpTable);	
}

void insertTree(char* key, AST A)
{
	if(symTable == NULL)
	{
	
		symTable = NEWARRAY(HASH,tableSize);
	}	

	if(((items * 1.0)/(tableSize*1.0)) > 0.7)
	{
		prevSize = tableSize;
		rehash();
	}

	int index;
	HASH hn;
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
		hn->funcName = key;
		hn->astTree = A;
		hn->next = NULL;
	}
	printf("Added %s\n",key);
	items = items + 1;		
}
