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

char* getMessageId(char* message, int messateType);

char* createElectionMessage(char* sendPort);

char* createElectionOverMessage(char* sendPort);

char* createContentMessage();




#endif /* MESSAGES_H_ */
