#include <stdio.h>
#include "stringtable.h"

int main() 
{
	printf("%s\n",intern("Hello World!"));
	printf("%s\n",intern("Add another"));
	printf("%s\n",intern("and another"));
	printf("%s\n",intern("Hello World!"));
	clearList();
	printf("%s\n",intern("Hello World!"));
	printf("%s\n",intern("Add another"));
	printf("%s\n",intern("and another"));
	printf("%s\n",intern("Hello World!"));
	clearList();
	clearList();
	return 0;
}
