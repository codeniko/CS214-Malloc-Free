#include "mymalloc.h"
#include <stdio.h>

void main()
{
    void* p = malloc(1);
    free(p);
    free(p);
}
