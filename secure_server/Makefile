CC = gcc
CFLAGS := -o
LDFLAGS := -std=c99 -lpthread

all: secure_server
	./secure_server

secure_server: main.c
	$(CC) $(CFLAGS) secure_server $(LDFLAGS) main.c