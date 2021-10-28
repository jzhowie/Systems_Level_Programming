struct city {
  char name[50];
  int pop;
  struct city *next;
};

void print_struct (struct city* m);
struct city * create_struct (char n[], int po);
void print_list(struct city *a);
struct city * insert_front(struct city *a, char n[], int po);
struct city * remove_node(struct city *front, int data);
struct city * free_list(struct city *start);
