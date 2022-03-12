#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/stat.h>

#define KEY 30040

int main(int argc, char*argv[]) {
  int f, shmd, semd;
  if (argv[1] == NULL) {
    printf("No argument detected.\n");
    printf("Valid arguments:\n");
    printf("-create to create a new file for telephone\n");
    printf("-remove to end telephone\n");
  }
  else if (strcmp(argv[1], "-create") == 0) {
    f = open("telephone", O_CREAT | O_RDWR | O_TRUNC, 0644);
    shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
    semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    union semun us;
    us.val = 1;
    semctl(semd, 0, SETVAL, us);
    printf("Initialized semaphore, shared memory, file\n");
  }
  else if (strcmp(argv[1], "-remove") == 0) {
    struct stat file;
    stat("telephone", &file);
    int size = file.st_size;
    char s[size];

    shmd = shmget(KEY, 0, 0);
    semd = semget(KEY, 1, 0);
    shmctl(shmd, IPC_RMID, 0);
    semctl(semd, IPC_RMID, 0);
    f = open("telephone", O_RDONLY);
    printf("Story so far:\n");
    read(f, s, size);
    printf("%s\n", s);
    close(f);
    printf("Removed semaphore, shared memory, file\n");
  }
  else {
    printf("Invalid argument.\n");
    printf("Valid arguments:\n");
    printf("-create to create a new file for telephone\n");
    printf("-remove to end telephone\n");
  }
  return 0;
}
