/*
 * File: node.c
 *
 * Date:        2017-08-27
 *
 *
 */
 
#include "node.h"


int main(int argc, char **argv) {

    host *thisHost;
    host *nextHost;

    int finished = 1;
    int send_socket;


    if (argc != 4) {
        printWrongParams(argv[0]);
        return EXIT_FAILURE;
    }


    thisHost = malloc(sizeof(host));
    thisHost->name = getCurrentHostName();
    thisHost->port = getIntFromStr(argv[1]);
    thisHost->finished = &finished;

    nextHost = malloc(sizeof(host));
    nextHost->name = argv[2];
    nextHost->port = getIntFromStr(argv[3]);





    /* Create receiver communication thread */
    pthread_t listenerThread;
    if (pthread_create(&listenerThread, NULL, &receiver_init, thisHost) < 0) {
        perror("Error creating listener-thread");
        return EXIT_FAILURE;
    }

    struct addrinfo *res;

    send_socket = setup_send_socket(nextHost);
    res = sender_connect(nextHost, send_socket);


    while(thisHost->finished){
    	send_message(res, send_socket);
    	sleep(4);
    	printf("receiver still alive\n");
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
            "<LISTEN_PORT> <SEND_TO_HOST> <SEND_TO_PORT>");
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


