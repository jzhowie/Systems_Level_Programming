#include "pipe_networking.h"
#include "connect_four.h"

void error_check( int i, char *s ) {
  if ( i < 0 ) {
    printf("[%s] error %d: %s\n", s, errno, strerror(errno) );
    exit(1);
  }
}

void files();

int main(int argc, char **argv) {

  int server;
  char buffer[BUFFER_SIZE];
  int board[42];

  printf("Connect Four\n");
  printf("[1] Play against server\n");
  printf("[2] Replay Game\n");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  int c = buffer[0] - '0';

  if (c == 1) {
  server = client_handshake(ADR);
  char user[31];
  printf("Enter username (up to 30 chars): ");
  fgets(user, sizeof(user), stdin);
  *strchr(user, '\n') = 0;

  write(server, user, sizeof(user));
    while (1) {
    read(server, board, sizeof(board));

      while (1) {
        print_board(board);
        printf("Enter 1-7: ");
        fgets(buffer, sizeof(buffer), stdin);
        *strchr(buffer, '\n') = 0;
        int x = buffer[0] - '0';

        while (x < 1 || x > 7 || drop_piece(board, x, 1) == -1) {
          printf("Enter 1-7: ");
          fgets(buffer, sizeof(buffer), stdin);
          *strchr(buffer, '\n') = 0;
          x = buffer[0] - '0';
        }
        write(server, buffer, sizeof(buffer));
        read(server, board, sizeof(board));
        if (check_board(board)) {
          printf("player %d wins\n", check_board(board));
          print_board(board);

          printf("save game? (y/n) ");
          fgets(buffer, sizeof(buffer), stdin);
          *strchr(buffer, '\n') = 0;

          write(server, buffer, sizeof(buffer));

          if (buffer[0] == 'y') {
            int turns[42];
            read(server, turns, sizeof(turns));

            printf("enter file name: ");
            fgets(buffer, sizeof(buffer), stdin);
            *strchr(buffer, '\n') = 0;
            sprintf(buffer, "%s.game", buffer);
            int f = open(buffer, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            write(f, turns, sizeof(turns));
            close(f);
          }
          printf("\n");
          read(server, board, sizeof(board));
          break;
        }
      }
    }
  }

  if (c == 2) {
    files();
  }
}

void files() {
  struct dirent *entry;
  struct stat file;
  DIR *d;
  char path[BUFFER_SIZE];

  printf("Searching for valid files...\n");
  getcwd(path, BUFFER_SIZE);
  d = opendir(path);

  printf("Valid files:\n");
  char *name;
  while (entry) {
    name = strstr(entry->d_name, ".game");
    if (name != NULL) printf("%s\n", entry->d_name);
    entry = readdir(d);
  }

  printf("Enter file name: ");
  fgets(path, sizeof(path), stdin);
  *strchr(path, '\n') = 0;

  int f = open(path, O_RDONLY);
  while (f < 0) {
    printf("Enter file name: ");
    fgets(path, sizeof(path), stdin);
    *strchr(path, '\n') = 0;
    f = open(path, O_RDONLY);
  }

  int turns[42];
  int board[42];

  int i;
  for (i = 0; i < 42; i++) {
    board[i] = 0;
  }
  read(f, turns, sizeof(turns));

  for (i = 0; turns[i] > 0 && turns[i] < 8 && i < 42; i++) {
    printf("Turn %d:\n" , i+1);
    drop_piece(board, turns[i], (i%2)+1);
    print_board(board);
    printf("\n");
  }

  close(f);
}
