#include "mymalloc.h"

void *mymalloc(int size, char *file, int line)
{
	if (mems == NULL) {
		if (size > MEMSPACE) {
			fprintf(stderr, "Insufficient memory space %d in file: '%s' on line: '%d'\n", size, __FILE__, __LINE__);
			return NULL;
		}
		MemEntry *n = (MemEntry *)malloc(sizeof(MemEntry));
		n->next = NULL;
		n->start = 0;
		n->end = size;
		mems = n;
		return memory; //return first index
	}

	MemEntry *cur = NULL;
	MemEntry *prev = NULL;
	int pEnd = -1;
	MemEntry *n = NULL; //memory node that is inserted, if inserted
	//if malloc successful, need to insert BEFORE cur
	for (cur = mems; ; cur = cur->next, prev = cur) {
		if (cur == NULL && size < MEMSPACE - pEnd) { //insert at end or beginning
			n = (MemEntry *)malloc(sizeof(MemEntry));
			n->next = NULL;
			n->start = pEnd+1;
			n->end = size-1;
			if (prev == NULL) { //first insertion
				mems = n;
			} else { //insert at end
				prev->next = n;
			}
			return memory + n->start;
		}
		else if (size < cur->start - pEnd) { //insert in beginning or before existing
			n = (MemEntry *)malloc(sizeof(MemEntry));
			n->next = NULL;
			n->start = pEnd+1;
			n->end = size-1;
			if (prev == NULL) { //insert in beginning
				n->next = mems;
				mems = n;
			} else { //insert before cur
				n->next = cur;
				prev->next = n;
			}
			return memory + n->start;
		}
	}

	// If reached, unable to allocate memory space
	if (n == NULL) {
		fprintf(stderr, "Insufficient memory space %d in file: '%s' on line: '%d'\n", size, __FILE__, __LINE__);
		return NULL;
	}
}

void myfree(void *p, char *file, int line)
{
	MemEntry *cur = NULL;
	MemEntry *prev = NULL;

	//NULL POINTER
	if (p == NULL) {
		fprintf(stderr, "ERROR: Pointer is NULL in file: '%s' on line: '%d'\n", __FILE__, __LINE__);
		return;
	}

	for (cur = mems; cur != NULL; cur = cur->next, prev = cur) {
		//check if pointer is in our alloc entries
		if (p == memory + cur->start)
		{
			if (prev == NULL && cur->next == NULL) {
				//last entry, set global mems to NULL
				free(cur);
				mems = NULL;
				return;
			} else if (prev == NULL) {
				//first entry
				mems = cur->next;
				free(cur);
				return;
			} else {
				//entry is in middle or end
				prev->next = cur->next;
				free(cur);
				return;
			}
		}
	}
	fprintf(stderr, "ERROR: Unable to free, pointer not allocated: '%s' on line: '%d'\n", __FILE__, __LINE__);
	return;
}
