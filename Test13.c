#include "mymalloc.h"
#include <stdio.h>

void main()
{
    void* p;
    int i;
    for(i = 1; (p = malloc(i % 2 == 0 ? 1 : 30)) != NULL; i++){
        printf("%d items allocated\n", i);
    }
}
