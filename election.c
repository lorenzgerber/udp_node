/*
 * election.c
 *
 *  Created on: Sep 7, 2017
 *      Author: lgerber
 */

#include "election.h"

int processMessage(char* ourId, char** receiveBuf, char** sendBuf, int** mode){



	int messageType;

	int election = 1;
	int electionOver = 2;
	int master = 3;
	int slave = 4;

	char * messageId = (char*) calloc(100, sizeof(char));


	messageType = checkMessageType(*receiveBuf);

	if(**mode == election){
		if (messageType == MSG_ELECTION){
			//char* messageId = getMessageId(receiveBuffer, 8);
			getMessageId2(*receiveBuf, 8, &messageId);

			int result = strcmp(ourId, messageId);
			if (result == 0){
				printf("we are the Elected!\n");
				*mode = &electionOver;

			}
			if (result < 0){
				copyReceiveToSend(receiveBuf, sendBuf);
			}
		} else if(messageType == MSG_ELECTION_OVER){
			*mode = &slave;

			printf("we are the slave\n");
			copyReceiveToSend(receiveBuf, sendBuf);
		}

	} else if(**mode == electionOver){
		if(messageType == MSG_ELECTION_OVER){
			createContentMessage(sendBuf);
			*mode = &master;

		}
	} else if (**mode == slave){
		if(messageType == MSG_CONTENT){
			createContentMessage(sendBuf);

		}
	} else if (**mode == master){
		if(messageType == MSG_CONTENT){
			createContentMessage(sendBuf);
		}
	}

	free(messageId);

	return 0;
}
