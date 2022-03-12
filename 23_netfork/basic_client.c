#include "pipe_networking.h"

int main() {
  int from_server;
  char buffer[255];

  from_server = client_handshake();

  while (1) {
    printf("Input: ");

    while (fgets(buffer, sizeof(buffer), stdin)) {
      write(from_server, buffer, sizeof(buffer));
      read(from_server, buffer, sizeof(buffer));
      printf("Output: %s\n", buffer);
      printf("Input: ");
    }
  }

  return 0;
}
