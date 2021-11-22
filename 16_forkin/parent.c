#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
  int p = getpid();
  int d;
  printf("forking...\n");
  d = fork();
  if (d) {
    fork();
  }
  if (p == getpid()) {
    int f, status;
    f = wait(&status);
    printf("pid: %d\ttime slept: %d\n", f, WEXITSTATUS(status));
    printf("parent is done\n");
  }
  else {
    printf("im a miner\t pid: %d\n", getpid());
    srand(getpid());
    int dur = (rand() % 4) + 2;
    sleep(dur);
    printf("miner is done\n");
    return dur;
  }
  return 0;
}
