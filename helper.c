/*
 * helper.c
 *
 *  Created on: Sep 7, 2017
 *      Author: lgerber
 */

#include "helper.h"

/* Will take the given string and return a allocated integer of the
 * string representation.
 *  @param givenStr The string that will remade to a int.
 *  @return         Integer pointer of the the given string
 */
int* getIntFromStr(char *givenStr) {
    int p;
    int *fixedInt;
    char *strRest;
    if ((p = strtol(givenStr, &strRest, 10)) == 0) {
        return NULL;
    }
    fixedInt = malloc(sizeof(int)*strlen(givenStr));
    *fixedInt = p;
    return fixedInt;
}

/* Will allocate a string and set the current hostname.
 * @return  current hostname.
 */
char* getCurrentHostName() {
    char tmpHost[255];
    memset(tmpHost, 0, 255);
    if (gethostname(tmpHost, 255) != 0) {
        return 0;
    }
    char *host = calloc(strlen(tmpHost)+1, sizeof(char));
    strcpy(host, tmpHost);
    return host;
}

char* getCurrentId(char* sendPort){
	char tmpHost[255];
	memset(tmpHost, 0, 255);
	if (gethostname(tmpHost, 255) != 0) {
		return 0;
	}
	char *host = calloc(strlen(tmpHost)+5, sizeof(char));
	strcpy(host, tmpHost);
	char*ptr = host;
	strcpy(&ptr[strlen(tmpHost)], sendPort);
	strcpy(&ptr[strlen(tmpHost)+4],"\0");

	return host;
}
