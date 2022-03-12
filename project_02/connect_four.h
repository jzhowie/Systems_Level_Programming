#include <stdlib.h>
#include <stdio.h>

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"

void print_board(int *board);
int drop_piece(int *board, int col, int p);
int check_board(int *board);
int check_rows(int *board);
int check_cols(int *board);
int neg_check_dias(int *board);
int pos_check_dias(int *board);
