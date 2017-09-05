/*
 * messages.c
 *
 *  Created on: Sep 5, 2017
 *      Author: lgerber
 */
#include "messages.h"

int checkMessageType(char* message){
	int length = 0;
	char*ptr = message;
	for (int i = 0; i < 100; i++){
		if(ptr[i]== '\n'){
			length = i;
			break;
		}
	}

	// currently for debugging
	printf("length %d\n", length);
	return length;
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
	strcpy(&ptr[14], tmpHost);
	strcpy(&ptr[14+strlen(tmpHost)], sendPort);
	strcpy(&ptr[18+strlen(tmpHost)],"\n");

	return message;

}

char* createContentMessage(){
	char *message = calloc(100, sizeof(char));
	strcpy(message, "MESSAGE\nI'm a normal Message\n");
	return message;

}
