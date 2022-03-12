#include "pipe_networking.h"

int server_setup() {
  struct addrinfo * hints, * results;

  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  getaddrinfo(NULL, PORT, hints, &results);  //Server sets node to NULL
  //create socket
  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  if (sd == -1) printf("%s\n", strerror(errno));

  bind(sd, results->ai_addr, results->ai_addrlen);

  free(hints);
  freeaddrinfo(results);

  return sd;
}

int server_connect(int sd) {
  listen(sd, 10);
  int client_socket;
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  client_socket = accept(sd, (struct sockaddr *) &client_address, &sock_size);

  // printf("%d\n", sd);
  // printf("%d\n", client_socket);
  return client_socket;
}

int client_handshake() {
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  getaddrinfo(ADR, PORT, hints, &results);  //Server sets node to NULL
  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  if (sd == -1) printf("%s\n", strerror(errno));

  connect(sd, results->ai_addr, results->ai_addrlen);
  free(hints);
  freeaddrinfo(results);
  return sd;
}
