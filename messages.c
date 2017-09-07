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
	return length;
}


int getMessageId(char* message, int messageType, char** messageId){
	int length = 0;
	char*ptr = message;

	for(int i = messageType+1; i < 100-messageType; i++){
		if(ptr[i]== '\n'){
			length = i;
			break;
		}
	}

	memcpy(*messageId, &ptr[messageType+1], length-(messageType+1));
	return 0;
}

int createElectionMessage(char* listenPort, char** sendBuf){
	char tmpHost[100];
	memset(tmpHost, 0, 100);
	if(gethostname(tmpHost, 100) != 0){
		return 0;
	}
	char *message = calloc(100, sizeof(char));

	strcpy(message, "ELECTION\n");
	char*ptr = message;
	strcpy(&ptr[9], tmpHost);
	strcpy(&ptr[9+strlen(tmpHost)], listenPort);
	strcpy(&ptr[13+strlen(tmpHost)],"\n");

	memcpy(*sendBuf, message, 100);
	free(message);

	return 0;
}


int createElectionOverMessage(char* listenPort, char**sendBuf){
	char tmpHost[100];

	if(gethostname(tmpHost, 100) != 0){
		return 0;
	}
	char *message = calloc(100, sizeof(char));

	strcpy(message, "ELECTION_OVER\n");
	char*ptr = message;
	strcpy(&ptr[14], tmpHost);
	strcpy(&ptr[14+strlen(tmpHost)], listenPort);
	memcpy(*sendBuf, message, 100);
	free(message);

	return 0;
}

int copyReceiveToSend(char** receiveBuf, char** sendBuf){
	memcpy(*sendBuf, *receiveBuf,100);
	return 0;
}


int createContentMessage(char** sendBuf){
	char *message = calloc(100, sizeof(char));
	strcpy(message, "MESSAGE\nI'm a normal Message\n");
	memcpy(*sendBuf, message, 100);
	free(message);

	return 0;
}
