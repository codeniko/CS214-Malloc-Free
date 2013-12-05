#include "mymalloc.h"

void main()
{
	void *p = mymallocd(25000);
	printf("p 25000 '%p'\n", p);
	void *p2 = mymallocd(1000);
	void *p3 = mymallocd(6000);
	printf("p2 1000 '%p'\n", p2);
	printf("p3 6000 '%p'\n", p3);
	void *p4 = mymallocd(20000);
	printf("p4 20000 '%p'\n", p4);

	printf("Freeing p\n");
	myfreed(p);
	printf("Freeing p2\n");
	myfreed(p2);
	printf("Freeing p3\n");
	myfreed(p3);
	printf("Freeing p4\n");
	myfreed(p4);
	printf("Freeing p3\n");
	myfreed(p3);
}
