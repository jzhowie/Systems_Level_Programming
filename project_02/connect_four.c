#include "connect_four.h"

// variable moves to track moves
// int main() {
//   int board[42];
//   int i;
//   for (i = 0; i < 42; i++) {
//     board[i] = 0;
//   }
//
//   print_board(board);
//
//   i = 1;
//   int j;
//   for (i = 1; i <= 6; i++) {
//     for (j = 0; j < 3; j++) {
//       // drop_piece(board, i, 1);
//       // print_board(board);
//       // printf("%d\n", check_rows(board));
//     }
//   }
//   drop_piece(board, 2, 1);
//   drop_piece(board, 3, 1);
//   drop_piece(board, 3, 1);
//   drop_piece(board, 4, 1);
//   drop_piece(board, 4, 1);
//   drop_piece(board, 4, 1);
//
//
//   drop_piece(board, 1, 2);
//   drop_piece(board, 2, 2);
//   drop_piece(board, 3, 2);
//   drop_piece(board, 4, 2);
//   // printf("%d\n", check_cols(board));
//   // printf("%d\n", check_board(board));
//   printf("%d\n", check_board(board));
//
//   print_board(board);
//   return 0;
// }

void print_board(int *board) {
  int i;
  for (i = 0; i < 42; i++) {
    if (board[i] == 1) {
      printf(RED);
      printf("o ");
    }
    else if (board[i] == 2) {
      printf(GRN);
      printf("o ");
    }
    else {
      printf(BLK);
      printf("o ");
    }

    if (i % 7 == 6) {
      printf(BLK);
      printf("\n");
    }
  }
  printf(BLK);
  // printf("------------------\n");
   // printf("^ ^ ^ ^ ^ ^ ^\n");
   // printf("1 2 3 4 5 6 7\n\n");
}

int drop_piece(int *board, int col, int p) {
  int c = col - 1;
  if (c >= 0 && c <= 6 && board[c] == 0) {
    int i = 0;
    while (i <= 4 && board[c+7*(i+1)] == 0) {
      i++;
    }

    board[c+7*i] = p;
    return 0;
  }
  return -1;
}

int check_board(int *board) {
  int r = check_rows(board);
  int c = check_cols(board);
  int nd = neg_check_dias(board);
  int pd = pos_check_dias(board);
  if (r > 0) return r;
  else if (c > 0) return c;
  else if (nd > 0) return nd;
  else if (pd > 0) return pd;
  else return 0;
}

int check_rows(int *board) {
  int r;
  for (r = 0; r < 6; r++) {
    int s;
    for (s = 0; s < 4; s++) {
      if (board[7*r+s] != 0 && board[7*r+s] == board[7*r+s+1] && board[7*r+s+1] == board[7*r+s+2] && board[7*r+s+2] == board[7*r+s+3]) {
        return board[7*r+s];
      }
    }
  }
  return 0;
}

int check_cols(int *board) {
  int c;
  for (c = 0; c < 7; c++) {
    int s;
    for (s = 0; s < 3; s++) {
      if (board[7*s+c] != 0 && board[7*s+c] == board[7*(s+1)+c] && board[7*(s+1)+c] == board[7*(s+2)+c] && board[7*(s+2)+c] == board[7*(s+3)+c]) {
        return board[7*s+c];
      }
    }
  }
  return 0;
}

// Diagonal check going from top-left to bottom-right
int neg_check_dias(int *board) {
  int d = 14;
  int dia[6];
  int i, s;
  while (d >= 7) {
    int start = d;
    for (i = 0; start < 42 && i < 6; i++) {
      dia[i] = board[start];
      // printf("%d, ", dia[i]);
      start = start + 8;
    }

    for (s = 0; s < 3; s++) {
      if (dia[s] != 0 && dia[s] == dia[s+1] && dia[s+1] == dia[s+2] && dia[s+2] == dia[s+3]) {
        return dia[s];
      }
    }
    // printf("\n");
    //operation
    d = d - 7;
  }
  while (d <= 3) {
    int start = d;
    for (i = 0; i < 6; i++) {
      dia[i] = board[start];
      // printf("%d, ", dia[i]);
      if (start % 7 == 6) break;
      start = start + 8;
    }

    for (s = 0; s < 3; s++) {
      if (dia[s] != 0 && dia[s] == dia[s+1] && dia[s+1] == dia[s+2] && dia[s+2] == dia[s+3]) {
        return dia[s];
      }
    }
    // printf("\n");
    //operation
    d++;
  }
  // printf("\n");
  return 0;
}

// Diagonal check going from top-right to bottom-left
int pos_check_dias(int *board) {
  int d = 20;
  int dia[6];
  int i, s;
  while (d >= 7) {
    for (i = 0; i < 6; i++) {
      dia[i] = 0;
    }

    int start = d;
    for (i = 0; start < 42 && i < 6; i++) {
      dia[i] = board[start];
      // printf("%d, ", dia[i]);
      start = start + 6;
    }

    for (s = 0; s < 3; s++) {
      if (dia[s] != 0 && dia[s] == dia[s+1] && dia[s+1] == dia[s+2] && dia[s+2] == dia[s+3]) {
        return dia[s];
      }
    }
    // printf("\n");
    //operation
    d = d - 7;
  }
  while (d >= 3) {
    for (i = 0; i < 6; i++) {
      dia[i] = 0;
    }

    int start = d;
    for (i = 0; i < 6; i++) {
      dia[i] = board[start];
      // printf("%d, ", dia[i]);
      if (start % 7 == 0) break;
      start = start + 6;
    }

    for (s = 0; s < 3; s++) {
      if (dia[s] != 0 && dia[s] == dia[s+1] && dia[s+1] == dia[s+2] && dia[s+2] == dia[s+3]) {
        return dia[s];
      }
    }

    // printf("\n");
    //operation
    d--;
  }
  // printf("\n");
  return 0;
}
