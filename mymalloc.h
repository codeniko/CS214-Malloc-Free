#ifndef _mymalloc_h_
#define _mymalloc_h_

#include <stdlib.h>
#include <stdio.h>

#define MEMSPACE 20000
#define mymallocd( x ) mymalloc( x , __FILE__ , __LINE__ )
#define myfreed( x ) myfree( x , __FILE__ , __LINE__ )



//linked list structure holding memory allocations
typedef struct MemEntry MemEntry;
struct MemEntry 
{
	MemEntry *next;
	int start; //index of memory alloc start
	int end; //index of memory alloc end
};

static char memory[MEMSPACE];
static MemEntry *mems = NULL;

void *mymalloc(int size, char *file, int line);
void myfree(void *p, char *file, int line);

#endif
