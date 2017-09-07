/*
 * election.h
 *
 *  Created on: Sep 7, 2017
 *      Author: lgerber
 */

#ifndef ELECTION_H_
#define ELECTION_H_
#define MSG_ELECTION 8
#define MSG_ELECTION_OVER 13
#define MSG_CONTENT 7
//#define MODE_ELECTION 1
//#define MODE_ELECTION_OVER 2
//#define MODE_MASTER 3
//#define MODE_SLAVE 4
#define NEW_MESSAGE 1
#include <time.h>
#include "messages.h"

int processMessage(char* ourId, char** receiveBuff, char** sendBuff, int** mode);

#endif /* ELECTION_H_ */

