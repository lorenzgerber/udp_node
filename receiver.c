/*
 * File: receiver.c
 *
 * Date:        2017-08-27
 *
 *
 */
#include "receiver.h"


void cleanup(void* arg){

	((host*) arg)->finished = 0;
}


/* Sets up a socket for receiving messages for the program
 * @param arg   host of the program.
 * @returned    void pointer (needed to end the thread)
 */
void *receiver_init(void *arg) {
    host *ht = (host*)arg;
    int sfd, s;
    int yes = 1;
    struct addrinfo hints, *result, *rp;


    pthread_cleanup_push(cleanup, ht);

    char *listeningPort = calloc(sizeof(char),16);
    sprintf(listeningPort, "%d", *ht->port);

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    /* Get addrinfo for the receiving part */
    s = getaddrinfo(NULL, listeningPort, &hints, &result);
    if (s != 0) {
       fprintf(stderr, "Receiver, could not find host: %s\n", gai_strerror(s));
       exit(EXIT_FAILURE);
    }
    /* Find correct address and try to bind a socket */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;
        if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))==-1) {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;
       close(sfd);
    }
    if (rp == NULL) {
        perror("Receiver, could not bind");
       exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);
    /* Choose listener. */

    fprintf(stderr,
            "Receiver, is now listening on %s port TCP.\n",
            listeningPort);
    receiver_listenTCP(ht, sfd);
    shutdown(sfd, SHUT_RDWR);


    /* listen-function has stopped, close and free */
    close(sfd);
    free(listeningPort);
    pthread_cleanup_pop(1);
    return NULL;
}


/* Will receive and save messages to the hostControll, uses protocol TCP.
 * @param   ht  The host of the program.
 * @param   sfd The socket it will receive data to.
 */
void receiver_listenTCP(host *ht, int sfd){

	ssize_t nread;
    int bufSize = sizeof(char)*BUF_SIZE;
    struct sockaddr_in client;
    int client_sock;
    int c;
    int exitLoop = 0;
    listen(sfd, 3);


    while(!exitLoop) {

        c = sizeof(struct sockaddr_in);
        client_sock = accept(sfd,(struct sockaddr *)&client, (socklen_t*)&c);

        if(client_sock < 0){
            perror("Receiver - accept failed");
            exit(EXIT_FAILURE);
        }

        while (!exitLoop) {

            char *buf = calloc(1, bufSize);
            nread = recv(client_sock, buf, bufSize, 0);
            if(nread == -1)
                continue;


            // Here have to implement interpreting the incoming message.
            fprintf(stdout, "%s", buf);

            if(strstr(buf, "EXIT") != NULL){
                exitLoop = 1;
            }

            if(nread == 0){
                fprintf(stderr, "Receiver - Client disconnected\n");
                fflush(stderr);
                break;
            }
            free(buf);
        }
        shutdown(client_sock, SHUT_RDWR);
        close(client_sock);
    }
}



