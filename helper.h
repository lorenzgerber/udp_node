/*
 * helper.h
 *
 *  Created on: Sep 7, 2017
 *      Author: lgerber
 */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#ifndef HELPER_H_
#define HELPER_H_
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int* getIntFromStr(char *givenStr);

char* getCurrentHostName();

char* getCurrentId(char* sendPort);


#endif /* HELPER_H_ */
