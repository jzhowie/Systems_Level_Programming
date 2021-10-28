#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
  struct city *front;
  front = NULL;

  printf("print_list() test: \n");
  print_list(front);

  printf("\ninsert_front() test: \n");
  front = insert_front(front, "New York City", 1634);
  front = insert_front(front, "Portland", 1851);
  front = insert_front(front, "San Francisco", 1776);
  front = insert_front(front, "Boston", 1630);
  print_list(front);

  printf("\nremove_node() test: \n");

  printf("\nRemoving Nothing:\n");
  front = remove_node(front, 0);
  print_list(front);

  printf("\nRemoving Front of Linked List:\n");
  print_list(front);
  front = remove_node(front, 1630);
  print_list(front);
  front = remove_node(front, 1776);
  print_list(front);
  front = remove_node(front, 1851);
  print_list(front);
  front = remove_node(front, 1634);
  print_list(front);

  front = insert_front(front, "New York City", 1634);
  front = insert_front(front, "Portland", 1851);
  front = insert_front(front, "San Francisco", 1776);
  front = insert_front(front, "Boston", 1630);

  printf("\nRemoving Randomly:\n");
  print_list(front);
  front = remove_node(front, 1776);
  print_list(front);
  front = remove_node(front, 1630);
  print_list(front);
  front = remove_node(front, 1851);
  print_list(front);
  front = remove_node(front, 1634);
  print_list(front);

  front = insert_front(front, "New York City", 1634);
  front = insert_front(front, "Portland", 1851);
  front = insert_front(front, "San Francisco", 1776);
  front = insert_front(front, "Boston", 1630);

  printf("\nRemoving Back of List:\n");
  print_list(front);
  front = remove_node(front, 1634);
  print_list(front);
  front = remove_node(front, 1851);
  print_list(front);
  front = remove_node(front, 1776);
  print_list(front);
  front = remove_node(front, 1630);
  print_list(front);

  front = insert_front(front, "New York City", 1634);
  front = insert_front(front, "Portland", 1851);
  front = insert_front(front, "San Francisco", 1776);
  front = insert_front(front, "Boston", 1630);
  
  printf("\nfree_list() test: \n");
  front = free_list(front);
  printf("Address of start node: %p\n", front);
  print_list(front);

  return 0;
}
