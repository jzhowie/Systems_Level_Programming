#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
  DIR *d;
  char buffer[255];
  if (argv[1] == NULL) {
    printf("Input file directory: \n");
    fgets(buffer, sizeof(buffer) - 1, stdin);
    int i = 0;
    while (buffer[i]) {
      i++;
    }
    buffer[i-1] = 0;
    d = opendir(buffer);
  }
  else {
    d = opendir(argv[1]);
  }
  if (d == NULL) {
    printf("%s\n", strerror(errno));
    return 1;
  }

  struct dirent *entry;
  struct stat file;

  entry = readdir(d);
  printf("Statistics for directory: %s\n", buffer);
  printf("Directories:\n");
  while (entry) {
    if (entry->d_type == 4) {
      printf("%s\n", entry->d_name);
    }
    entry = readdir(d);
  }

  int size = 0;
  rewinddir(d);
  printf("\nFiles:\n");
  entry = readdir(d);
  while (entry) {
    if (entry->d_type == 8) {
      printf("%s\t", entry->d_name);
      stat(entry->d_name, &file);
      size += file.st_size;
      printf("%lld\n", file.st_size);
    }
    entry = readdir(d);
  }
  closedir(d);
  printf("Total Directory Size: %d bytes\n", size);

  return 0;
}
