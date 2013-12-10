#include "mymalloc.h"
#include <stdio.h>

void main()
{
        printf("mallocing p 25000\n");
        void *p = malloc(25000);
        printf("p 25000 '%p'\n", p);
        printf("mallocing p2 1000\n");
        void *p2 = malloc(1000);
        printf("p2 1000 '%p'\n", p2);
        printf("mallocing p4 should be success 20000\n");
        void *p4 = malloc(20000);
        printf("p4 20000 '%p'\n", p4);
        printf("Freeing p4\n");
        free(p4);

        printf("mallocing p3 6000\n");
        void *p3 = malloc(6000);
        printf("p3 6000 '%p'\n", p3);
        printf("mallocing p4 20000\n");
        p4 = malloc(20000);
        printf("p4 20000 '%p'\n", p4);

        printf("Freeing p\n");
        free(p);
        printf("Freeing p2\n");
        free(p2);
        printf("Freeing p3\n");
        free(p3);
        printf("Freeing p4\n");
        free(p4);
        printf("Freeing p3\n");
        free(p3);
}
