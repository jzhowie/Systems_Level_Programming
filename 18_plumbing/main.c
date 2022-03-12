#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define READ 0
#define WRITE 1


int main() {
  int desc[2];
  pipe(desc);

  int f = fork();

  if (f) {
    char buffer[255];
    printf("Input: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(desc[WRITE], buffer, sizeof(buffer));
    close(desc[WRITE]);
    while (read(desc[READ], buffer, sizeof(buffer))) {
      printf("Output: %s", buffer);
    }
  }
  else {
    char buffer[255];
    read(desc[READ], buffer, sizeof(buffer));

    int i = 0;
    while (buffer[i] != '\n') {
      if (islower(buffer[i])) buffer[i] = 'a' + ((buffer[i] + 13 - 'a') % 26);
      else if (isupper(buffer[i])) buffer[i] = 'A' + ((buffer[i] + 13 - 'A') % 26);
      i++;
    }
    close(desc[READ]);
    write(desc[WRITE], buffer, sizeof(buffer));
  }
  return 0;
}
