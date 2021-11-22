#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static void sighandler(int signo) {
  if (signo == SIGINT) {
    int f = open("run.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
    char a[100] = "Program exited due to SIGINT\n";
    write(f, a, sizeof(a));
    close(f);
    exit(0);
  }
  if (signo == SIGUSR1) {
    printf("ppid: %d\n", getppid());
  }
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while (1) {
    printf("pid: %d\n", getpid());
    sleep(1);
  }
  return 0;
}
