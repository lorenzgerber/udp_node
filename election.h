/*
 * election.h
 *
 *  Created on: Sep 7, 2017
 *      Author: lgerber
 */

#ifndef ELECTION_H_
#define ELECTION_H_
#include <time.h>
#include "messages.h"

int processMessage(char* ourId, char** receiveBuff, char** sendBuff, int** mode, char* port);

#endif /* ELECTION_H_ */

