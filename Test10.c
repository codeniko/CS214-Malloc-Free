#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    void* p = malloc(sizeof(int));
    *((int*)p) = 5;
    printf("integer: address: %p, value: %d\n", p, *((int*)p));
    free(p);
    char* c = "Hello World"; 
    p = malloc(sizeof(char) * (strlen(c) + 1));
    memcpy(p, c, strlen(c));
    printf("String: address: %p, value: %s\n", p, (char*)p);
    free(p);
    p = malloc(sizeof(float));
    *((float*)p) = 1.2345;
    printf("float: address: %p, value: %f\n", p, *((float*)p));
    free(p);
}
