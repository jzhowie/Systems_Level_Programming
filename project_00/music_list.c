#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "music_list.h"

void print_struct (struct song_node* m) {
  if (m) printf("%s: %s", m->name, m->artist);
  else printf("Song doesn't exist!");
}

struct song_node* create_struct (char n[], char a[]) {
  struct song_node *p = malloc(sizeof(struct song_node));
  strcpy(p->name, n);
  strcpy(p->artist, a);

  // int i;
  // for (i = 0; i < 100; i++) {
  //   p->name[i] = tolower((unsigned char) p->name[i]);
  //   p->artist[i] = tolower((unsigned char) p->artist[i]);
  // }

  p->next = NULL;
  return p;
}

void print_list(struct song_node *a) {
  printf("[");
  while (a) {
    print_struct(a);
    a = a->next;
    if (a) printf(" | ");
  }
  printf("]\n");
}

struct song_node * search_artist(struct song_node *front, char a[]) {
  struct song_node *temp = front;
  while (temp) {
    if (strcasecmp(front->artist, a) == 0) return temp;
    temp = temp->next;
  }
  return 0;
}

struct song_node * search_song(struct song_node *front, char n[], char a[]) {
  struct song_node *temp = front;
  while (temp) {
    if (strcasecmp(temp->artist, a) == 0 && strcasecmp(temp->name, n) == 0) return temp;
    temp = temp->next;
  }
  return 0;
}

struct song_node * random_node(struct song_node *front) {
  int size = 0;
  struct song_node *temp = front;
  while (temp) {
    size++;
    temp = temp->next;
  }
  temp = front;
  if (size) {
    int pos = generate_random() % size;
    int i;
    for (i = pos; pos > 0; pos--) {
      temp = temp->next;
    }
    return temp;
  }
  return 0;
}

struct song_node * insert_front(struct song_node *prev, char n[], char a[]) {
  struct song_node *p = create_struct(n, a);
  p->next = prev;
  return p;
}

struct song_node * insert_sorted(struct song_node *front, char n[], char a[]) {
  struct song_node *p = create_struct(n, a);
  if (front == NULL) return p;
  if (compare_nodes(p, front) < 0) {
    p->next = front;
    front = p;
    return front;
  }
  struct song_node *temp;
  temp = front;
  while (temp->next) {
    if (compare_nodes(p, temp) < 0) {
      p->next = temp->next;
      temp->next = p;
      return front;
    }
    temp = temp->next;
  }
  p->next = temp->next;
  temp->next = p;
  return front;
}

struct song_node * remove_node(struct song_node *front, char n[], char a[]) {
  struct song_node *temp;
  if (strcasecmp(front->artist, a) == 0 && strcasecmp(front->name, n) == 0) {
    temp = front->next;
    free(front);
    return temp;
  }
  temp = front;
  while (temp->next) {
    if (strcasecmp(temp->next->artist, a) == 0 && strcasecmp(temp->next->name, n) == 0) {
      struct song_node *c = temp->next;
      temp->next = temp->next->next;
      free(c);
      return front;
    }
    temp = temp->next;
  }
  return front;
}

struct song_node * free_list(struct song_node *start) {
  struct song_node *b;
  while (start) {
    b = start;
    start = start->next;
    free(b);
  }
  return start;
}

int compare_nodes(struct song_node *a, struct song_node *b) {
  int compare = strcasecmp(a->artist, b->artist);
  if (compare) return compare;
  else {
    compare = strcasecmp(a->name, b->name);
    if (compare) return compare;
    else return 0;
  }
}

int generate_random() {
  return rand();
}
