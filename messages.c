/*
 * messages.c
 *
 *  Created on: Sep 5, 2017
 *      Author: lgerber
 */
#include "messages.h"

int checkMessageType(char* message){

	return 0;
}

char* createElectionMessage(char* sendPort){
	char tmpHost[100];
	memset(tmpHost, 0, 100);
	if(gethostname(tmpHost, 100) != 0){
		return 0;
	}
	char *message = calloc(100, sizeof(char));

	strcpy(message, "ELECTION\n");
	char*ptr = message;
	strcpy(&ptr[9], tmpHost);
	strcpy(&ptr[9+strlen(tmpHost)], sendPort);
	strcpy(&ptr[13+strlen(tmpHost)],"\n");

	return message;

}

char* createElectionOverMessage(char* sendPort){
	char tmpHost[100];
	memset(tmpHost, 0, 100);
	if(gethostname(tmpHost, 100) != 0){
		return 0;
	}
	char *message = calloc(100, sizeof(char));

	strcpy(message, "ELECTION_OVER\n");
	char*ptr = message;
	strcpy(&ptr[9], tmpHost);
	strcpy(&ptr[9+strlen(tmpHost)], sendPort);
	strcpy(&ptr[13+strlen(tmpHost)],"\n");

	return message;

}

char* createContentMessage(){
	char *message = calloc(100, sizeof(char));
	strcpy(message, "MESSAGE\nI'm a normal Message\n");
	return message;

}
