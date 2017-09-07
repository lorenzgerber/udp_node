/*
 * election.c
 *
 *  Created on: Sep 7, 2017
 *      Author: lgerber
 */
#define MSG_ELECTION 8
#define MSG_ELECTION_OVER 13
#define MSG_CONTENT 7
#define MODE_ELECTION 1
#define MODE_ELECTION_OVER 2
#define MODE_MASTER 3
#define MODE_SLAVE 4
#define NEW_MESSAGE 1

#include "election.h"

int processMessage(char* ourId, char** receiveBuf, char** sendBuf, int** mode, char*port){

	int messageType;
	char * messageId = (char*) calloc(100, sizeof(char));
	messageType = checkMessageType(*receiveBuf);


	switch (**mode){
	case MODE_ELECTION:
		election(ourId, mode, messageType, messageId,receiveBuf, sendBuf, port);
		break;
	case MODE_ELECTION_OVER:
		if(messageType == MSG_ELECTION_OVER){
			createContentMessage(sendBuf);
			**mode = MODE_MASTER;
		}
		break;
	case MODE_SLAVE:
		if(messageType == MSG_CONTENT){
			createContentMessage(&*sendBuf);
		}
		break;
	case MODE_MASTER:
		if(messageType == MSG_CONTENT){
			createContentMessage(&*sendBuf);
		}
	}

	return 0;
}



int election(char* ourId, int** mode, int messageType, char* messageId, char** receiveBuf, char** sendBuf, char* port){
	if (messageType == MSG_ELECTION){
		getMessageId(*receiveBuf, 8, &messageId);
		int result = strcmp(ourId, messageId);
		free(messageId);

		if (result == 0){
			printf("we are the Elected!\n");
			**mode = MODE_ELECTION_OVER;
			createElectionOverMessage(port, &*sendBuf);
		}
		if (result < 0){
			copyReceiveToSend(receiveBuf, &*sendBuf);
		}
	} else if(messageType == MSG_ELECTION_OVER){
		**mode = MODE_SLAVE;

		printf("we are the slave\n");
		copyReceiveToSend(receiveBuf, &*sendBuf);
	}

	return 0;
}
