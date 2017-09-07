/*
 * sender.h
 *
 *  Created on: Sep 4, 2017
 *      Author: lgerber
 */

#include "receiver.h"
#ifndef SENDER_H_
#define SENDER_H_


int setup_send_socket();

struct addrinfo *get_server_address(host *ht);

int connect_to_server(int sock, host *ht, struct addrinfo *res);

void send_message(int sock, struct addrinfo *res, char* message);


#endif /* SENDER_H_ */
