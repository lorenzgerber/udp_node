/*
 * File: node.c
 *
 * Date:        2017-08-27
 *
 *
 */
 
#include "node.h"


int main(int argc, char **argv) {
    host *hc;
    if (argc != 3) {
        printWrongParams(argv[0]);
        return EXIT_FAILURE;
    }

    /* Programname need concist of tcp or udp in its name */
    if(strstr(argv[1], "tcp") == NULL
      && strstr(argv[1], "udp") == NULL) {
        printWrongParams(argv[0]);
        return EXIT_FAILURE;
    }
    hc = malloc(sizeof(host));
    hc->name = getCurrentHostName();
    hc->port = getIntFromStr(argv[2]);
    hc->isUDP = (strstr(argv[1], "udp") != NULL) ? 0 : 1;
    /* Create receiver communication thread */
    pthread_t listenerThread;
    if (pthread_create(&listenerThread, NULL, &receiver_init, hc) < 0) {
        perror("Error creating listener-thread");
        return EXIT_FAILURE;
    }
    pthread_join(listenerThread, NULL);

    fprintf(stderr, "Exit-message received, goodbye!\n");
    return EXIT_SUCCESS;
}
void printWrongParams(char *progName) {
    fprintf(stderr,
            "%s\n%s %s\n",
            "Invalid parameters",
            progName,
            "<[tcp|udp]> <PORT>");
}
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
