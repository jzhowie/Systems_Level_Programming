#include <stdio.h>

unsigned int problem_5();
unsigned int problem_7();

int main() {
  printf("Problem 5 - Smallest positive number divisible by all of the numbers from 1 to 20: %d\n", problem_5());
  printf("Problem 7 - 10001st prime: %d\n", problem_7());
  return 0;
}

unsigned int problem_5() {
  unsigned int count = 20;
  char a = 1;
  for (a = 1; a < 21; a++) {
    if (count % a != 0) {
      count++;
      a = 1;
    }
  }
  return count;
}

unsigned int problem_7() {
  unsigned int prime = 2;
  unsigned int a = 1;
  short count = 1;
  while (count <= 10001) {
    for (a = 2; a <= prime / 2; a++) {
      if (prime % a == 0) {
        prime++;
        a = 2;
      }
    }
    prime++;
    count++;
  }
  return prime - 1;
}
