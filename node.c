/*
 * File: node.c
 *
 * Date:        2017-08-27
 *
 *
 */
 
#include "node.h"
pthread_mutex_t mtx_lock;


int main(int argc, char **argv) {

    host *thisHost;
    host *nextHost;
    struct addrinfo *res;
    char* sendBuffer = (char*) calloc(100, sizeof(char));


    int election = 1;
    int electionOver = 2;
    int master = 3;
    int slave = 4;
    int *mode = &election;

    // variables to synchronize read/send of messages
    int noMessage = 0;
    int newMessage = 1;
    int *gotMessage = &noMessage;



    int finished = 1;
    int send_socket = -1;


    if (argc != 4) {
        printWrongParams(argv[0]);
        return EXIT_FAILURE;
    }

    // initialize lock
    pthread_mutex_init(&mtx_lock, NULL);

    // set host struct of our host
    thisHost = malloc(sizeof(host));
    thisHost->name = getCurrentHostName();
    thisHost->port = getIntFromStr(argv[1]);
    thisHost->finished = &finished;
    thisHost->sendBuffer = &sendBuffer;
    thisHost->gotMessage = &gotMessage;
    thisHost->mode = &mode;

    // set host struct of send-to host
    nextHost = malloc(sizeof(host));
    nextHost->name = argv[2];
    nextHost->port = getIntFromStr(argv[3]);


    // Create receiver communication thread
    pthread_t listenerThread;
    if (pthread_create(&listenerThread, NULL, &receiver_init, thisHost) < 0) {
        perror("Error creating listener-thread");
        return EXIT_FAILURE;
    }

    // set up sender
    res = get_server_address(nextHost);
    send_socket = setup_send_socket();

    int connected = -1;
    sendBuffer = createElectionMessage(argv[1]);


    // try to connect
    while(connected < 0){
    	connected = connect_to_server(send_socket, nextHost, res);
    	printf("waiting to get send connection\n");
    	sleep(2);
    }

    // send first message
    send_message(send_socket, res, createElectionMessage(argv[1]));




    // send loop as long as receiver is alive
    while(thisHost->finished){

    	// only send new message when you got one
    	if(*gotMessage == newMessage){

			if (*mode == election){
				send_message(send_socket, res, sendBuffer);
			} else if (*mode == electionOver){
				send_message(send_socket, res, createElectionOverMessage(argv[1]));
			} else if (*mode == master || *mode == slave){
				send_message(send_socket, res, sendBuffer);
			}

			pthread_mutex_lock(&mtx_lock);
			gotMessage = &noMessage;
			pthread_mutex_unlock(&mtx_lock);

    	}
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








