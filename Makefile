COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: malloc

malloc.o: malloc.c malloc.h
	$(COMPILER) $(CFLAGS) -c malloc.c

main.o: main.c malloc.h
	$(COMPILER) $(CFLAGS2) -c main.c
	
malloc: malloc.o main.o
	$(COMPILER) $(CFLAGS) -o main.o malloc.o
	
clean:
	rm -f *.o malloc
