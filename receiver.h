/*
 * File: receiver.h
 *
 * Date:        2017-08-27
 *
 */
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <net/if.h>
#include <math.h>
#include "messages.h"
#define BUF_SIZE 100
#define NI_MAXHOST 1025
#define NI_MAXSERV 32
#define MSG_ELECTION 8
#define MSG_ELECTION_OVER 13
#define MSG_CONTENT 7
#define MODE_ELECTION 1
#define MODE_ELECTION_OVER 2
#define MODE_MASTER 3
#define MODE_SLAVE 4
#define NEW_MESSAGE 1
#ifndef __RECEIVER
#define __RECEIVER

// data transfer struct
typedef struct host {
	char ** sendBuffer;
    char *name;
    int *port;
    int *finished;
    int **gotMessage;
    int **mode;
}host;

// global mutex lock
extern pthread_mutex_t mtx_lock;

/* Sets up a socket for receiving messages for the program
 * @param arg   hostController of the program.
 * @returned    void pointer (needed to end the thread)
 */
void *receiver_init(void *arg);
/* Will receive and print to the host, uses protocol UDP.
 * @param   ht      The host of the program
 * @param   sfd     The socket it will receive data to.
 */
void receiver_listenUDP(host *ht, int sfd);
/* Will receive and print messages to the host, uses protocol TCP.
 * @param   ht      The host of the program
 * @param   sfd     The socket it will receive data to.
 */
void receiver_listenTCP(host *ht, int sfd);


char* getCurrentId(char* sendPort);

#endif
