struct song_node{
char name[100];
char artist[100];
struct song_node *next;
};

void print_struct (struct song_node* m);
void print_list(struct song_node *a);
int generate_random();

struct song_node * search_artist(struct song_node *front, char a[]);
struct song_node * search_song(struct song_node *front, char n[], char a[]);
struct song_node * random_node(struct song_node *front);

struct song_node * create_struct (char n[], char a[]);
struct song_node * insert_front(struct song_node *prev, char n[], char a[]);
struct song_node * insert_sorted(struct song_node *front, char n[], char a[]);
int compare_nodes(struct song_node *a, struct song_node *b);

struct song_node * remove_node(struct song_node *front, char n[], char a[]);
struct song_node * free_list(struct song_node *start);
