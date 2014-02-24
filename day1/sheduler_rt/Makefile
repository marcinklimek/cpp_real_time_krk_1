CC=gcc
CFLAGS=-lpthread

all: fifo_1 fifo_2 fifo_3 normal rr_1 rr_2 rr_3

rr_1:	rr_1.c
	$(CC) $^ $(CFLAGS) -o $@

rr_2:	rr_2.c
	$(CC) $^ $(CFLAGS) -o $@

rr_3:	rr_3.c
	$(CC) $^ $(CFLAGS) -o $@

fifo_1:	fifo_1.c
	$(CC) $^ $(CFLAGS) -o $@

fifo_2:	fifo_2.c
	$(CC) $^ $(CFLAGS) -o $@

fifo_3:	fifo_3.c
	$(CC) $^ $(CFLAGS) -o $@

normal:	normal.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm - fr *o fifo_1 fifo_2
