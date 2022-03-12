#include "pipe_networking.h"

static void sighandler(int signo) {
  if (signo == SIGINT) {
    //write(to_client, "//7\n", 5);
    exit(0);
  }
}

int main() {

  int to_client;
  int from_client;
  char buffer[255];
  signal(SIGINT, sighandler);

  while (1) {
    from_client = server_handshake( &to_client );
    printf("%d\n", to_client);

  while (1) {
    if (read(from_client, buffer, sizeof(buffer)) == 0) break;
    printf("Recieved %s", buffer);

      int i = 0;
      while (buffer[i] != '\n') {
        if (islower(buffer[i])) buffer[i] = 'a' + ((buffer[i] + 13 - 'a') % 26);
        else if (isupper(buffer[i])) buffer[i] = 'A' + ((buffer[i] + 13 - 'A') % 26);
        i++;
      }

      write(to_client, buffer, sizeof(buffer));
  }
  }

  return 0;
}
