# Makefile
CC=gcc
CFLAGS= -Wall -std=c99 -pedantic -g -pthread

all: node

node: node.c receiver.c sender.c messages.c election.c receiver.h node.h sender.h messages.h election.h
	$(CC) $(CFLAGS) -o node node.c receiver.c sender.c messages.c election.c
	
clean:
	rm node
