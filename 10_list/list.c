#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void print_struct (struct city* m) {
  printf("{%s, %d}", m->name, m->pop);
}

struct city* create_struct (char n[], int po) {
  struct city *p = malloc(sizeof(struct city));
  strcpy(p->name, n);
  p->pop = po;
  p->next = NULL;
  return p;
}

void print_list(struct city *a) {
  printf("[");
  while (a) {
    print_struct(a);
    a = a->next;
    printf(", ");
  }
  printf("]\n");
}

struct city * insert_front(struct city *a, char n[], int po) {
  struct city *p = create_struct(n, po);
  p->next = a;
  return p;
}

struct city * remove_node(struct city *front, int data) {
  struct city *temp;
  if (front->pop == data) {
    temp = front->next;
    free(front);
    return temp;
  }
  temp = front;
  while (temp->next) {
    if (temp->next->pop == data) {
      struct city *c = temp->next;
      temp->next = temp->next->next;
      free(c);
      return front;
    }
    temp = temp->next;
  }
  return front;
}

struct city * free_list(struct city *start) {
  struct city *b;
  while (start) {
    b = start;
    start = start->next;
    free(b);
  }
  return start;
}
