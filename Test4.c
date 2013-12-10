#include "mymalloc.h"
#include <stdio.h>

void main()
{
    int i;
    int* p = malloc(5 * sizeof(int));
    for(i = 0; i < 5; i++){
        p[i] = i;
    }
    for(i = 0; i < 5; i++){
        printf("address: %p, value: %d\n", p + i, p[i]);
     }
    free(p);
}
