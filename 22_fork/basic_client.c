#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;
  char buffer[255];

  from_server = client_handshake( &to_server );

  while (1) {
    printf("Input: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(to_server, buffer, sizeof(buffer));
    read(from_server, buffer, sizeof(buffer));
    printf("Output: %s\n", buffer);
  }

  return 0;
}
