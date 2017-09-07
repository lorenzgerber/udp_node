# Makefile
CC=gcc
CFLAGS= -Wall -std=c99 -Werror -g -pthread

all: node

node: node.c receiver.c sender.c messages.c election.c helper.c receiver.h node.h sender.h messages.h election.h helper.h
	$(CC) $(CFLAGS) -o TcpNode node.c receiver.c sender.c messages.c election.c helper.c
	
clean:
	rm TcpNode
