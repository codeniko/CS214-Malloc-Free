#include "mymalloc.h"
#include <stdio.h>

void main()
{
    int* p = malloc(sizeof(int));
    *p = 5;
    printf("address: %p, value: %d\n",p, *p);
    free(p);
}
