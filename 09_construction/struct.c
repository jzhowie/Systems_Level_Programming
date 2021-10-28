#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player {
  char name[50];
  int num;
};

void print_struct (struct player* m) {
  printf("Player %d: %s\n", m->num, m->name);
}

struct player* create_struct (char n[], int i) {
  struct player *p = malloc(sizeof(struct player));
  strcpy(p->name, n);
  p->num = i;

  return p;
}

int main() {
  struct player *g = create_struct("Gi-Hun", 456);
  print_struct(g);
  free(g);

  struct player *f = create_struct("Sang-woo", 211);
  (*f).num = 218;
  print_struct(f);
  free(f);

  struct player *k = create_struct("Sae-byeok", 67);
  print_struct(k);
  free(k);

  return 0;
}
