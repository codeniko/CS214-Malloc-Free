COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: mymalloc
.PHONY: all
.PHONY: clean

mymalloc.o: mymalloc.c mymalloc.h
	$(COMPILER) $(CFLAGS) -c mymalloc.c

main.o: main.c mymalloc.h
	$(COMPILER) $(CFLAGS2) -c main.c
	
mymalloc: mymalloc.o main.o
	$(COMPILER) $(CFLAGS) -o mymalloc main.o mymalloc.o
	
clean:
	rm -f *.o mymalloc
