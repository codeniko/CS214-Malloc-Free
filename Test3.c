#include "mymalloc.h"
#include <stdio.h>

void main()
{
    int i;
    for(i = 0; i < 5; i++){
        int* p = malloc(sizeof(int));
        *p = i;
        printf("address: %p, value: %d\n",p, *p);
    }
}
