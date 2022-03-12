#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/stat.h>

#define READ 0
#define WRITE 1

int main() {
  int fd, fd2;
  mkfifo("input", 0644);
  mkfifo("output", 0644);
  fd = open("input", O_RDONLY);
  fd2 = open("output", O_WRONLY);

  char buffer[255];
  read(fd, buffer, sizeof(buffer));
  close(fd);

  int i = 0;
  while (buffer[i] != '\n') {
    if (islower(buffer[i])) buffer[i] = 'a' + ((buffer[i] + 13 - 'a') % 26);
    else if (isupper(buffer[i])) buffer[i] = 'A' + ((buffer[i] + 13 - 'A') % 26);
    i++;
  }
  write(fd2, buffer, sizeof(buffer));
  close(fd2);
  return 0;
}
