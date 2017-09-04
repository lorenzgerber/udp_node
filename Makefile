# Makefile
CC=gcc
CFLAGS= -Wall -std=c99 -pedantic -g -pthread

all: node

node: node.c receiver.c receiver.h node.h
	$(CC) $(CFLAGS) -o node node.c receiver.c
	
clean:
	rm node
