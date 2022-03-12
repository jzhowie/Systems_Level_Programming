#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo(WKP, 0644);
  char buffer[BUFFER_SIZE];
  printf("Opened server!\n");
  int p1 = open(WKP, O_RDONLY);
  *to_client = p1;

  if (p1 == -1) printf("%s\n", strerror(errno));
  else printf("Connection to client opened!\n");

  if (read(p1, buffer, HANDSHAKE_BUFFER_SIZE) > 0) {
      printf("Read %s from ACK pipe (SYN).\n", buffer);
      remove(WKP);
  }
  else {
    printf("No bytes read.\n");
  }

  int p2 = open(buffer, O_WRONLY);
  int from_client = p2;
  if (write(p2, buffer, HANDSHAKE_BUFFER_SIZE) > 0) {
    printf("Wrote %s to ACK (SYN_ACK).\n", buffer);
  }
  else {
    printf("No bytes written.\n");
  }

  if (read(p1, buffer, BUFFER_SIZE) > 0) {
    printf("Recieved %s from ACK (ACK).\n", buffer);
  }
  else {
    printf("No bytes read.\n");
  }

  printf("Handshake complete!\n");
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char buffer[BUFFER_SIZE];
  sprintf(buffer, "%d", getpid());
  mkfifo(buffer, 0644);
  printf("Opened client!\n");
  int p1 = open(WKP, O_WRONLY);
  *to_server = p1;

  if (p1 == -1) printf("%s\n", strerror(errno));
  else printf("Connected to server!\n");

  if (write(p1, buffer, HANDSHAKE_BUFFER_SIZE) > 0) printf("Wrote %s to WKP (SYN).\n", buffer);
  else printf("No bytes written.\n");

  int p2 = open(buffer, O_RDONLY);
  int from_server = p2;

  if (p2 == -1) printf("%s\n", strerror(errno));
  else printf("Secret pipe opened!\n");

  if (read(p2, buffer, BUFFER_SIZE) > 0) {
    printf("Recieved %s from WKP (SYN_ACK).\n", buffer);
  }
  else {
    printf("No bytes read.\n");
  }

  remove(buffer);
  if (write(p1, buffer, BUFFER_SIZE) > 0) {
    printf("Wrote %s to WKP (ACK).\n", buffer);
  }
  else {
    printf("No bytes written.\n");
  }

  printf("Handshake complete!\n");
  return from_server;
}
