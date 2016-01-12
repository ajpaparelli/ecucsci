#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringtable.h"
#include "allocate.h"

struct Node
{
	char* data;
	struct Node* next;
};


struct Node* stringList;

char* perm(const char* s)
{
	char* result = NEWARRAY(char, strlen(s)+1);
	strcpy(result,s);
	return result;
}

char* intern(const char* s)
{
	struct Node* currptr;
  	if(stringList == NULL)
	{
		stringList = NEW(struct Node);
		stringList->data = perm(s);
		stringList->next = NULL;
		return stringList->data;
	}		
	else
	{
		currptr = stringList;
		while(currptr != NULL)
		{
			if(strcmp(s,currptr->data) == 0)
			{
				return currptr->data;
			}
			else if(currptr->next == NULL)
			{
				currptr->next = NEW(struct Node);
				currptr = currptr->next;
				currptr->data = perm(s);
				currptr->next = NULL;
				return currptr->data;
			}
			else
				currptr = currptr->next;
		}
		return NULL;
	}	
}

void clearList()
{
	if(stringList != NULL)
	{		
		struct Node* currptr = stringList;
		struct Node* temp;
		while(currptr != NULL)
		{
			temp = currptr;
			currptr = currptr->next;
			free(temp);
		}
		stringList = NULL;
	}
}
	


