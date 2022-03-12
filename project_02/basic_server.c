#include "pipe_networking.h"
#include "connect_four.h"
#define KEY 109018

int process(char *s, int *board, int *turns, int moves);
void update_statistics(int c);
void print_leaderboard();
void update_leaderboard(int *b);
void init_leaderboard();
void subserver(int client_1);

struct player {
  char user[31];
  int wins;
};

static void sighandler(int signo) {
  if (signo == SIGINT) {
    int shmd = shmget(KEY, 0, 0);
    int global_plays = shmget(KEY+1, 0, 0);
    shmctl(shmd, IPC_RMID, 0);
    shmctl(global_plays, IPC_RMID, 0);
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  srand(time(NULL));

  int listen_socket;
  int f;

  int shmd = shmget(KEY, sizeof(struct player) * 10, IPC_CREAT | 0640);
  int global_plays = shmget(KEY+1, sizeof(int), IPC_CREAT | 0640);
  // init_leaderboard();
  listen_socket = server_setup();


  while (1) {
    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0)
      subserver(client_socket);
    else
      close(client_socket);
  }
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  int board[42];
  int i;
  int moves = 0;
  int turns[42];
  struct player *b = calloc(1, sizeof(struct player));
  for (i = 0; i < 42; i++) {
    board[i] = 0;
  }

  read(client_socket, b->user, sizeof(b->user));
  write(client_socket, board, sizeof(board));

  while (read(client_socket, buffer, sizeof(buffer)) > 0) {
    printf("[subserver %d] move %d\n", getpid(), moves);
    printf("[subserver %d] received from S1: [%s]\n", getpid(), buffer);

    int c = process(buffer, board, turns, moves);
    if (c) {
      if (c == 1) {
        b->wins++;
        // update_leaderboard((int *)&b);
      }
      update_statistics(c);
      print_leaderboard();

      write(client_socket, board, sizeof(board));
      read(client_socket, buffer, sizeof(buffer));

      if (buffer[0] == 'y') {
        write(client_socket, turns, sizeof(turns));
      }

      int i;
      for (i = 0; i < 42; i++) {
        board[i] = 0;
      }

      moves = 0;
      write(client_socket, board, sizeof(board));
    }

    print_board(board);
    write(client_socket, board, sizeof(board));
    moves++;
    moves++;
  }//end read loop
  free(b);
  close(client_socket);
  exit(0);
}

int process(char *s, int *board, int *turns, int moves) {
  int x = s[0] - '0';
  drop_piece(board, x, 1);
  turns[moves] = x;
  if (check_board(board) == 1) return 1;
  int p = (rand() % 7) + 1;
  while (drop_piece(board, p, 2) < 0) {
    p = (rand() % 7) + 1;
  }
  turns[moves+1] = p;
  if (check_board(board) == 2) return 2;
  if (moves >= 40) return -1;
  return 0;
}

void update_statistics(int c) {
  int shmd = shmget(KEY+1, 0, 0);
  int *data = shmat(shmd, 0, 0);
  (*data)++;

  shmdt(data);
}

void update_leaderboard(int *c) {
  struct player *b = (struct player *)c;
  int shmd = shmget(KEY, 0, 0);
  struct player *data = shmat(shmd, 0, 0);

  struct player *temp = data;
  if (b->wins > (data+10)->wins) {
    int i;
    while (i < 10 && strcmp(temp->user, b->user) != 0) {
      temp++;
      i++;
    }
    if (strcmp(temp->user, b->user) == 0) {
      temp->wins = b->wins;
      return;
    }

    i = 9;
    temp = data + i;
    while (i > 0 && b->wins > temp->wins) {
      strcpy((temp-1)->user, temp->user);
      (temp-1)->wins = temp->wins;
      temp--;
      i--;
    }
    strcpy(temp->user, b->user);
    temp->wins = b->wins;
  }
  shmdt(data);
}

void init_leaderboard() {
  int shmd = shmget(KEY, 0, 0);
  struct player *data = shmat(shmd, 0, 0);

  int i;
  for (i = 0; i < 10; i++) {
    sprintf(data->user, "holder");
    data->wins = -1;
    data++;
  }
  shmdt(data);
}

void print_leaderboard() {
  int shmd = shmget(KEY+1, 0, 0);
  int shmd_board = shmget(KEY, 0, 0);
  int *data = shmat(shmd, 0, 0);
  struct player *leaderboard = shmat(shmd_board, 0, 0);

  printf("Global Plays: %d\n", *data);

  // struct player *b = leaderboard;
  // int i;
  // for (i = 0; i < 10; i++) {
  //   printf("%d. %s\t\t%d\n", i+1, b->user, b->wins);
  //   b++;
  // }
  // printf("\n");

  shmdt(data);
  shmdt(leaderboard);
}
