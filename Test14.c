#include "mymalloc.h"
#include <stdio.h>

void main()
{
    void* p;
    int i;
    for(i = 1; (p = malloc(1)) != NULL; i++){
        printf("%d items allocated\n", i);
    }
}
