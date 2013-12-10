#include "mymalloc.h"
#include <stdio.h>

void main()
{
    void* p;
    int i;
    for(i = 1; (p = malloc(i)) != NULL; i++){
        printf("%d bytes allocated\n", i);
    }
}
