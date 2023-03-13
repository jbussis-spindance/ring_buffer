CC=clang
CFLAGS=-std=c99 -Wall -Wextra -Werror

all: main

main: main.o ring_buffer.o
	$(CC) $(CFLAGS) -o main main.o ring_buffer.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

ring_buffer.o: ring_buffer.c ring_buffer.h
	$(CC) $(CFLAGS) -c ring_buffer.c

clean:
	rm -f main *.o
