#include "pipe_networking.h"

int main() {
  int socke;
  int client;
  char buffer[255];
  socke = server_setup();
  while (1) {
    client = server_connect(socke);
    // printf("%d\n", from_client);

    int f = fork();
    if (f) {
      while (1) {
        while (read(client, buffer, sizeof(buffer)) > 0) {
        printf("Recieved %s", buffer);

          int i = 0;
          while (buffer[i] != '\n') {
            if (islower(buffer[i])) buffer[i] = 'a' + ((buffer[i] + 13 - 'a') % 26);
            else if (isupper(buffer[i])) buffer[i] = 'A' + ((buffer[i] + 13 - 'A') % 26);
            i++;
          }

          write(client, buffer, sizeof(buffer));
        }
      }
    }
    else {
      close(client);
    }
  }
  return 0;
}
