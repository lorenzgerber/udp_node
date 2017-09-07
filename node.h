/*
 * File: node.h
 *
 * Date:        2017-08-27
 *
 */

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "receiver.h"
#include "messages.h"
#include "sender.h"
#include "helper.h"
#ifndef __NODE
#define __NODE

void printWrongParams(char *progName);
/* Will take the given string and return a allocated integer of the
 * string representation.
 *  @param  givenStr    The string that will remade to a int.
 *  @return Integer pointer of the the given string
 */
int* getIntFromStr(char *givenStr);
/* Will allocate a string and set the current hostname.
 * @return  Current hostname
 */
char* getCurrentHostName();

char* getCurrentId(char* sendPort);


#endif
