#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_array(int *arr, int s);
float avg_array(int *arr, int s);
void copy_array(int *arr1, int *arr2, int s);

int main() {
  int size = 10;
  int i;
  int a[size];
  int b[size];
  srand(time(NULL));
  for (i = 0; i < 10; i++) {
    a[i] = rand() / 10000;
    b[i] = 1;
  }
  printf("Array A: ");
  print_array(a, size);
  printf("Average of A: %f\n", avg_array(a, size));

  printf("Copy Array Test: \n");
  printf("Array A: ");
  print_array(a, size);
  printf("Array B: ");
  print_array(b, size);

  copy_array(a, b, size);

  printf("New Array B: ");
  print_array(b, size);
}

void print_array(int *arr, int s) {
  int i;
  printf("[");
  for (i = 0; i < s; i++) {
    printf(" %d", *arr);
    arr++;
  }
  printf(" ]\n");
}

float avg_array(int *arr, int s) {
  int i;
  int sum = 0;
  for (i = 0; i < s; i++) {
    sum += *arr;
    arr++;
  }
  return sum / s;
}

void copy_array(int *arr1, int *arr2, int s) {
  int i;
  for (i = 0; i < s; i++) {
    *arr2 = *arr1;
    arr1++;
    arr2++;
  }
}
