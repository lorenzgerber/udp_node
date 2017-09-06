/*
 * messages.h
 *
 *  Created on: Sep 5, 2017
 *      Author: lgerber
 */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#ifndef MESSAGES_H_
#define MESSAGES_H_


int checkMessageType(char* message);

char* getMessageId(char* message, int messageType);

int getMessageId2(char* message, int messageType, char** messageId);

//char* createElectionMessage(char* sendPort);
int createElectionMessage(char* sendPort, char** sendBuff);

//char* createElectionOverMessage(char* sendPort);
int createElectionOverMessage(char* sendPort, char** sendBuff);

//char* createContentMessage();
int createContentMessage(char** sendBuf);

int copyReceiveToSend(char** receiveBuff, char** sendBuff);


#endif /* MESSAGES_H_ */
