struct song_node ** make_library();
void add_song(struct song_node** front, char n[], char a[]);
void remove_song(struct song_node ** front, char n[], char a[]);
void shuffle(struct song_node ** front, int t);

void print_library(struct song_node** front);
void print_letter(struct song_node** front, char c);
void print_artist(struct song_node** front, char a[]);
struct song_node ** free_library(struct song_node** front);

struct song_node * search_library(struct song_node ** front, char n[], char a[]);
struct song_node * search_artist_node(struct song_node ** front, char a[]);
