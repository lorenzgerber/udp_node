/*
 * File: receiver.c
 *
 * Date:        2017-08-27
 *
 *
 */
#define MSG_ELECTION 8
#define MSG_ELECTION_OVER 13
#define MSG_CONTENT 7
#define MODE_ELECTION 1
#define MODE_ELECTION_OVER 2
#define MODE_MASTER 3
#define MODE_SLAVE 4
#define NEW_MESSAGE 1

#include "receiver.h"


void cleanup(void* arg){

	((dataContainer*) arg)->finished = 0;
}


/* Sets up a socket for receiving messages for the program
 * @param arg   host of the program.
 * @returned    void pointer (needed to end the thread)
 */
void *receiver_init(void *arg) {
    dataContainer *ht = (dataContainer*)arg;

    pthread_cleanup_push(cleanup, ht);

    struct sockaddr_in addr;//, from;
	int sock;


	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(*(*ht->host)->port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (struct sockaddr *)&addr, sizeof (addr));



    receiver_listenTCP(ht, sock);

    close(sock);

    pthread_cleanup_pop(1);
    return NULL;
}

/* Will receive and save messages to the hostControll, uses protocol TCP.
 * @param   ht  The host of the program.
 * @param   sfd The socket it will receive data to.
 */
void receiver_listenTCP(dataContainer *ht, int sfd){


	char* ourId;
    int bufSize = sizeof(char)*BUF_SIZE;
    int client_sock;
    int exitLoop = 0;

    int rv;

    fd_set readfds;
    fcntl(sfd, F_SETFL, O_NONBLOCK);
    struct timeval tv;

    clock_t timeOutStart;
    clock_t timeOutCurrent;
    double timeOutSpent;


	int statCounter = 0;
	clock_t begin;
	clock_t end;
	double timeSpent = 0;

    char port[5];
    sprintf(port,"%d", *(*ht->host)->port);
    ourId = getCurrentId(port);

    while(!exitLoop) {

        client_sock = sfd;
        char *receiveBuffer = calloc(1, bufSize);

        //Start Timeout clock
        timeOutStart = clock();

        while (!exitLoop) {

        	timeOutCurrent=clock();
        	timeOutSpent = (double)(timeOutCurrent - timeOutStart) / CLOCKS_PER_SEC;
        	if(timeOutSpent > 5){
        		*ht->finished = 0;
        		exitLoop = 1;
        		printf("finished\n");
        	}

            int waitSend = 1;
			while (waitSend){
				if(**ht->gotMessage != 1){
					waitSend = 0;
				}
			}
			waitSend = 1;


        	FD_ZERO(&readfds);
			FD_SET(sfd, &readfds);

			tv.tv_sec = 0;
			tv.tv_usec = 0;

			rv = select(sfd + 1, &readfds, NULL, NULL, &tv);

			if(rv==1){
				recvfrom(client_sock, receiveBuffer, 100, 0, NULL, NULL);

				// Chang & Roberts Algo
				processMessage(ourId, &receiveBuffer, ht->sendBuffer, ht->mode, port);

				pthread_mutex_lock(&mtx_lock);
				**ht->gotMessage = NEW_MESSAGE;
				pthread_mutex_unlock(&mtx_lock);
				timeOutStart = clock();

				//Timing
				if(**ht->mode == MODE_MASTER){
					if (statCounter == 0){
						begin = clock();
						statCounter++;
					} else if (statCounter == 10000){
						end = clock();
						timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
						printf("time per 10000 RT's %f\n", timeSpent);
						statCounter = 0;
					} else {
						statCounter++;
					}
				}

			}
        }

        free(receiveBuffer);
        shutdown(client_sock, SHUT_RDWR);
        close(client_sock);
    }
}



