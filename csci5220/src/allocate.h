#include <stdlib.h>

#define NEW(T) ((T*) (malloc(sizeof(T))))

#define NEWARRAY(T,N) ((T*)(malloc((N)*(sizeof(T))))
