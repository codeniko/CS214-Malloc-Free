#include "mymalloc.h"

#define MEMSIZE 25000

struct MemEntry
{
	struct MemEntry *prev, *next;
	int isfree;		// 1 - yes, 0 - no
	int size;
};


static char memblock[MEMSIZE]; //big block of memory space
static const int entriesSize = MEMSIZE/sizeof(struct MemEntry)+1; //size of memEntries
static void *memEntries[MEMSIZE/sizeof(struct MemEntry)+1] = {0}; //pointers to memEntries


int getFreeIndex() {
	int i;
	for (i = 0; i < entriesSize; i++)
		if (memEntries[i] == 0) 
			return i;
	return 1; //should never reach here but 0 is always set as root
}

// return a pointer to the memory buffer requested
void *mymalloc(unsigned int size, char *file, int line)
{
	static int initialized = 0;
	static struct MemEntry *root;
	struct MemEntry *p;
	struct MemEntry *next;
	
	if (size == 0) {
		fprintf(stderr, "Unable to allocate 0 bytes in FILE: '%s' on LINE: '%d'\n", file, line);
		return 0;
	}

	if(!initialized)	// 1st time called
	{
		// create a root chunk at the beginning of the memory block
		root = (struct MemEntry*) memblock;
		root->prev = root->next = 0;
		root->size = MEMSIZE - sizeof(struct MemEntry);
		root->isfree = 1;
		initialized = 1;
		memEntries[getFreeIndex()] = memblock;
	}

	p = root;
	do
	{
		if(p->size < size || !p->isfree) {
			// the current chunk is smaller, go to the next chunk
			// or this chunk was taken, go to the next
			p = p->next;
		}
		else if(p->size < (size + sizeof(struct MemEntry))) {
			// this chunk is free and large enough to hold data, 
			// but there's not enough memory to hold the HEADER of the next chunk
			// don't create any more chunks after this one
			p->isfree = 0;
			return (char*)p + sizeof(struct MemEntry);
		}
		else {
			// take the needed memory and create the header of the next chunk
			next = (struct MemEntry*)((char*)p + sizeof(struct MemEntry) + size);
			next->prev = p;
			next->next = p->next;
			next->size = p->size - sizeof(struct MemEntry) - size;
			next->isfree = 1;
			memEntries[getFreeIndex()] = next;
			p->size = size;
			p->isfree = 0;
			p->next = next;
			return (char*)p + sizeof(struct MemEntry);
		}
	} while (p != 0);

	fprintf(stderr, "Insufficient memory space requested (%d bytes) in FILE: '%s' on LINE: '%d'\n", size, file, line);
	return 0;
}

// free a memory buffer pointed to by p
void myfree(void *p, char *file, int line)
{
	struct MemEntry *ptr;
	struct MemEntry *prev;
	struct MemEntry *next;

	if (p == NULL) {
		fprintf(stderr, "Pointer is NULL in file, free failed in FILE: '%s' on LINE: '%d'\n", file, line);
		return;
	}

	ptr = (struct MemEntry*)((char*)p - sizeof(struct MemEntry));
	
	//check if valid memEntry ptr
	int i;
	int valid = 0;
	for (i = 0; i < entriesSize; i++) {
		if (ptr == memEntries[i]) {
			valid = 1; //memEntry is valid
			break;
		}
	}
	if (!valid) {
		fprintf(stderr, "Attempting to free memory that was not malloced in FILE: '%s' on LINE: '%d'\n", file, line);
		return;
	}

	if((prev = ptr->prev) != 0 && prev->isfree)
	{
		// the previous chunk is free, so
		// merge this chunk with the previous chunk
		prev->size += sizeof(struct MemEntry) + ptr->size;
		memEntries[i] = 0; //merged with previous, so removing free memEntry
	}
	else
	{ //not setting memEntry to null b/c not necessarily removing it, just isfree=1
		ptr->isfree = 1;
		prev = ptr;	// used for the step below
	}
	if((next = ptr->next) != 0 && next->isfree)
	{
		// the next chunk is free, merge with it
		prev->size += sizeof(struct MemEntry) + next->size;
		//prev->isfree = 1;
		for (i = 0; i < entriesSize; i++) {
			if (next == memEntries[i]) {
				memEntries[i] = 0; //merged with next, so removing free memEntry
				break;
			}
		}
	}
}
