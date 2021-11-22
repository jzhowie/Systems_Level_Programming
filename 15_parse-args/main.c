#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char ** parse_args(char *line);

int main() {
  char cmd[] = "ls -a -l";
  printf("Command: %s\n", cmd);
  char **args = parse_args(cmd);
  printf("Executing...\n");
  execvp(args[0], args);
  // int i;
  // for (i = 0; i < 5; i++) {
  //   printf("%s\n", args[i]);
  // }
  free(args);
  return 0;
}

char ** parse_args(char *line) {
  int i = 0;
  char **args;
  args = malloc(sizeof(char *) * 5);
  char *curr = line;
  char *token;
  //printf("a\n");
  while (curr && i < 5) {
    token = strsep(&curr, " ");
    args[i] = token;
    printf("Argument %d: %s\n", i+1, token);
    i++;
  }
  return args;
}
