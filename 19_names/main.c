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
  fd = open("input", O_WRONLY);
  fd2 = open("output", O_RDONLY);

  char buffer[255];
  printf("Input: ");
  fgets(buffer, sizeof(buffer), stdin);
  write(fd, buffer, sizeof(buffer));
  close(fd);
  while (read(fd2, buffer, sizeof(buffer))) {
    printf("Output: %s", buffer);
  }
  close(fd2);
  return 0;
}
