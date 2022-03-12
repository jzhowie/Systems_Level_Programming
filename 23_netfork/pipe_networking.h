#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#ifndef NETWORKING_H
#define NETWORKING_H

#define PORT "50152"
#define ADR "127.0.0.1"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000


//for forking server
int server_setup();
int server_connect(int sd);

int client_handshake();

#endif
