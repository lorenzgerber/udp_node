/*
 * sender.c
 *
 *  Created on: Sep 4, 2017
 *      Author: lgerber
 */
#define _XOPEN_SOURCE 600
#define oops(s) {perror(s); exit(-1); }
#define BUFSIZE 100
#include "sender.h"

int setup_send_socket(){
	int sock;
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		perror("socket");

	return sock;
}

struct addrinfo *sender_connect(host *ht, int sock){

	int status;
	struct addrinfo *res, hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_ADDRCONFIG;


	/* Build the network address of server */
	char port[5];
	sprintf(port, "%d", *ht->port);

	status = getaddrinfo(ht->name,port , &hints, &res);
	switch (status) {
		/* Check errnos from getaddrinfo */
		case 0: // Success
			break;
		default:
			oops("getaddrinfo");
	}

	connect(sock, (struct sockaddr *)res->ai_addr, res->ai_addrlen);
	return res;

}

void send_message(struct addrinfo *res, int sock){

	char buf[BUFSIZE];
	sprintf(buf, "Some data\n");
	sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)res->ai_addr, res->ai_addrlen);

}


