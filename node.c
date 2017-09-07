/*
 * File: node.c
 *
 * Date:        2017-08-27
 *
 *
 */

#define MODE_ELECTION 1
#define MODE_ELECTION_OVER 2
#define MODE_MASTER 3
#define MODE_SLAVE 4
#define NO_MESSAGE 0
#define NEW_MESSAGE 1

#include "node.h"
pthread_mutex_t mtx_lock;

int main(int argc, char **argv) {

    //host *thisHost;
    host *thisHost;
    host *nextHost;
    dataContainer *dataTransfer;
    struct addrinfo *res;


    char* sendBuffer = (char*) calloc(100, sizeof(char));

    int election = 1;
    int *mode = &election;
    int newMessage = 1;
    int *gotMessage = &newMessage;

    int finished = 1;
    int send_socket = -1;

    // sanitize user input
    if (argc != 4) {
        printWrongParams(argv[0]);
        return EXIT_FAILURE;
    }

    // initialize lock
    pthread_mutex_init(&mtx_lock, NULL);


    // set host struct of send-to host
    nextHost = malloc(sizeof(host));
    nextHost->name = argv[2];
    nextHost->port = getIntFromStr(argv[3]);

    // set host struct of this host
    thisHost = malloc(sizeof(host));
    thisHost->name = getCurrentHostName();
    thisHost->port = getIntFromStr(argv[1]);

    // prepare data to be transered to receiver thread
    dataTransfer = malloc(sizeof(dataContainer));
    dataTransfer->host = &thisHost;
    dataTransfer->finished = &finished;
    dataTransfer->sendBuffer = &sendBuffer;
    dataTransfer->gotMessage = &gotMessage;
    dataTransfer->mode = &mode;

    // Create receiver communication thread
    pthread_t listenerThread;
    if (pthread_create(&listenerThread, NULL, &receiver_init, dataTransfer) < 0) {
        perror("Error creating listener-thread");
        return EXIT_FAILURE;
    }


    // set up sender
    res = get_server_address(nextHost);
    send_socket = setup_send_socket();

    //int connected = -1;
    createElectionMessage(argv[1], &sendBuffer);


    // send first message
    send_message(send_socket, res, sendBuffer);

    //got message, has to be 'yes' from start so that
    // receiver is blocked until we have sent first message
    // to not mess up the sendBuffer.
    pthread_mutex_lock(&mtx_lock);
	*gotMessage = NO_MESSAGE;
	pthread_mutex_unlock(&mtx_lock);

    // send loop as long as receiver is alive
    while(1){

    	if(*gotMessage == NEW_MESSAGE){

			if (*mode == MODE_ELECTION){
				send_message(send_socket, res, sendBuffer);
			} else if (*mode == MODE_ELECTION_OVER){
				send_message(send_socket, res, sendBuffer);
			} else if (*mode == MODE_MASTER || *mode == MODE_SLAVE){
				send_message(send_socket, res, sendBuffer);
			}

			pthread_mutex_lock(&mtx_lock);
			*gotMessage = NO_MESSAGE;
			pthread_mutex_unlock(&mtx_lock);
    	}
    }

    pthread_join(listenerThread, NULL);

    // clean up
    free(dataTransfer);
    free(thisHost);
    free(nextHost);

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









