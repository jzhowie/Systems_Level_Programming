#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "music_list.h"
#include "library.h"

struct song_node ** make_library() {
  struct song_node** library = calloc(27, sizeof(struct song_node*));
  return library;
}

void print_library(struct song_node** front) {
  int i;
  printf("==============\n");
  for (i = 0; i < 27; i++) {
    if (front[i]) {
      if (i == 26) printf("Non-alphanumeric: ");
      else printf("%c: ", 65+i);
      print_list(front[i]);
    }
  }
  printf("==============\n");
}

void print_letter(struct song_node** front, char c) {
  if (isalpha(c)) printf("%c: ", c);
  else printf("Non-alphanumeric: ");

  if (isupper(c)) print_list(front[c-65]);
  else if (isalpha(c)) print_list(front[c-97]);
  else print_list(front[26]);
}

void print_artist(struct song_node** front, char a[]) {
  struct song_node* temp = search_artist_node(front, a);
  printf("Songs by %s: ", a);
  while (temp && strcasecmp(temp->artist, a) == 0) {
    print_struct(temp);
    printf(" | ");
    temp++;
  }
}

void add_song(struct song_node** front, char n[], char a[]) {
  if (isupper(a[0])) front[a[0]-65] = insert_sorted(front[a[0]-65], n, a);
  else if (isalpha(a[0])) front[a[0]-97] = insert_sorted(front[a[0]-97], n, a);
  else front[26] = insert_sorted(front[26], n, a);
}

void remove_song(struct song_node ** front, char n[], char a[]) {
  if (isupper(a[0])) front[a[0]-65] = remove_node(front[a[0]-65], n, a);
  else if (isalpha(a[0])) front[a[0]-97] = remove_node(front[a[0]-97], n, a);
  else front[26] = remove_node(front[26], n, a);
}

struct song_node * search_library(struct song_node ** front, char n[], char a[]) {
  if (isupper(a[0])) return search_song(front[a[0]-65], n, a);
  else if (isalpha(a[0])) return search_song(front[a[0]-97], n, a);
  else return search_song(front[26], n, a);
}

struct song_node * search_artist_node(struct song_node ** front, char a[]) {
  if (isupper(a[0])) return search_artist(front[a[0]-65], a);
  else if (isalpha(a[0])) return search_artist(front[a[0]-97], a);
  else return search_artist(front[26], a);
}

void shuffle(struct song_node ** front, int t) {
  int i;
  int temp;
  for (i = 0; i < t; i++) {
    temp = generate_random() % 27;
    while (front[temp] == 0) {
      temp = generate_random() % 27;
    }
    print_struct(random_node(front[temp]));
    printf("\n");
  }
}

struct song_node ** free_library(struct song_node** front) {
  int i;
  for (i = 0; i < 27; i++) {
    front[i] = free_list(front[i]);
  }
  free(front);
  return front;
}
