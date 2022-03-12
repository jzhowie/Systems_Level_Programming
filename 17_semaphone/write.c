#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>

#define KEY 30040

int main() {
  int semd;
  int *data;
  char b[255];
  int fd = open("telephone", O_RDWR);
  int shmd = shmget(KEY, 0, 0);
  data = shmat(shmd, 0, 0);

  semd = semget(KEY, 1, 0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;

  semop(semd, &sb, 1);
  lseek(fd, -(*data), SEEK_END);
  read(fd, b, *data);
  printf("Last addition: %s\n", b);

  printf("Your addition: ");
  fgets(b, sizeof(b) - 1, stdin);
  int c = 0;
  int size = 0;
  while (b[c] != '\n') {
    size++;
    c++;
  }
  write(fd, b, size+1);

  *data = size+1;
  sb.sem_op = 1;
  semop(semd, &sb, 1);
  shmdt(data);
  return 0;
}
