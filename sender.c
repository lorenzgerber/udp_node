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

struct addrinfo *get_server_address(host *ht){
	struct addrinfo *res;
	struct addrinfo hints;
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = 0;
		hints.ai_flags = AI_ADDRCONFIG;

		//Translate server port to char
		char port[5];
			sprintf(port, "%d", *ht->port);

		/* Build the network address of server */
		getaddrinfo(ht->name, port, &hints, &res);

	return res;
}

int connect_to_server(int sock, host *ht, struct addrinfo *res){

	if(connect(sock, (struct sockaddr *)res->ai_addr, res->ai_addrlen) < 0)
		return -1;
	return 0;
}

void send_message(int sock, struct addrinfo *res, char* message){

	char buf[BUFSIZE];
	memset(buf, 0, 100);
	sprintf(buf, "%s\n", message);
	if(sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)res->ai_addr, res->ai_addrlen)<0)
		perror("sendto");
}


