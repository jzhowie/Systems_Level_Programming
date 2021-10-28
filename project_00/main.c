#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "music_list.h"
#include "library.h"

int main() {
  struct song_node *front;
  front = NULL;

  srand(time(NULL));

  printf("SONG NODE TESTING: \n");
  printf("print_list() test: \n");
  print_list(front);

  printf("\ninsert_front() test: \n");
  front = insert_front(front, "Stay", "Justin Bieber");
  front = insert_front(front, "6 Feet", "Juice WRLD");
  front = insert_front(front, "Industry Baby", "Lil Nas X");
  print_list(front);

  front = free_list(front);

  printf("\ncompare_nodes() test: \n");
  struct song_node *a = create_struct("6 Feet", "Juice WRLD");
  struct song_node *b = create_struct("Industry Baby", "Lil Nas X");
  struct song_node *c = create_struct("Maze", "Juice WRLD");
  printf("%d\n", compare_nodes(a, b));
  printf("%d\n", compare_nodes(b, c));
  printf("%d\n", compare_nodes(a, c));

  printf("\ninsert_sorted() test: \n");
  front = insert_sorted(front, "Stay", "Justin Bieber");
  front = insert_sorted(front, "6 Feet", "Juice WRLD");
  front = insert_sorted(front, "Industry Baby", "Lil Nas X");
  front = insert_sorted(front, "What's Next", "Drake");
  front = insert_sorted(front, "Chicago Freestyle", "Drake");
  print_list(front);

  printf("\nrandom_node() test: \n");
  print_struct(random_node(front));
  printf("\n");

  printf("\nsearch_node() test: \n");
  printf("Searching for artist named: Drake\n");
  print_struct(search_artist(front, "Drake"));
  printf("\n");
  printf("Searching for song named: Industry Baby\n");
  print_struct(search_song(front, "Industry Baby", "Lil Nas X"));
  printf("\n");
  printf("Searching for song named: Never Gonna Give You Up\n");
  print_struct(search_song(front, "Never Gonna Give You Up", "Rick Astley"));
  printf("\n");

  printf("\nremove_node() test: \n");
  print_list(front);
  front = remove_node(front, "6 Feet", "Juice WRLD");
  print_list(front);
  front = remove_node(front, "Industry Baby", "Lil Nas X");
  print_list(front);
  front = remove_node(front, "Stay", "Justin Bieber");
  print_list(front);

  printf("\nfree_list() test: \n");
  front = free_list(front);
  print_list(front);

  printf("\nLIBRARY TESTING: \n");
  struct song_node **library = make_library();
  add_song(library, "6 Feet", "Juice WRLD");
  add_song(library, "maze", "Juice WRLD");
  add_song(library, "industry Baby", "Lil Nas X");
  add_song(library, "Stay", "Justin Bieber");
  add_song(library, "never Gonna Give You Up", "Rick Astley");
  add_song(library, "Chicago Freestyle", "Drake");
  add_song(library, "Chicago Freestyle", "!Drake");

  printf("\nadd_song() testing: \n");
  print_library(library);
  printf("\n");

  printf("print_letter() testing: \n");
  print_letter(library, 'D');
  print_letter(library, 'B');

  printf("\nprint_artist() / search_artist() testing: \n");
  print_artist(library, "Juice WRLD");

  printf("\n\nsearch_library() testing: \n");
  printf("Searching for song named: Industry Baby\n");
  print_struct(search_library(library, "Industry Baby", "Lil Nas X"));
  printf("\n");
  printf("Searching for song named: Castaway\n");
  print_struct(search_library(library, "Castaway", "Juneau"));
  printf("\n");

  printf("\nremove_song() testing: \n");
  print_library(library);
  printf("Removing Stay by Justin Beiber (library stays the same)\n");
  remove_song(library, "Stay", "Justin Beiber");
  print_library(library);
  printf("Removing Stay by Justin Bieber\n");
  remove_song(library, "Stay", "Justin Bieber");
  print_library(library);

  printf("\nshuffle() testing: \n");
  printf("Adding songs...\n");
  add_song(library, "Moonlight Sonata", "Ludwig van Beethoven");
  add_song(library, "Piano Sonata No. 16", "Amadeus Mozart");
  add_song(library, "Piano Sonata No. 17", "Amadeus Mozart");
  add_song(library, "Gymnopedies No. 1", "Erik Satie");
  add_song(library, "The Blue Danube", "Johann Strauss II");
  print_library(library);
  shuffle(library, 5);

  printf("\nfree_library() testing: \n");
  library = free_library(library);
  print_library(library);

  return 0;
}
