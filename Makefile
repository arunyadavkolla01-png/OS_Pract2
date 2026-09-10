CC = gcc
CFLAGS = -Wall -g

prog1: prog1.c
	$(CC) $(CFLAGS) -o prog1 prog1.c

clean:
	rm -f prog1
prog3: prog3.c
	$(CC) $(CFLAGS) -o prog3 prog3.c
