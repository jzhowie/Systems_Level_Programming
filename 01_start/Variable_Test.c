#include <stdio.h>

int main() {
  int a = 4;
  printf("Int, Long, Double: %d %ld %f\n", a, (long) a, (double) a);

  long b = 4.000000000000 + 0.001;
  printf("%ld\n", b);

  int c = 2147483647;
  printf("Max: %d, Max+1: %d\n", c, c+1);

  signed int cd = 2147483647;
  printf("Signed Max: %d, Max+1: %d\n", cd, cd+1);

  char d = (char) 0;
  for (int i = 0; i < 500; i++) {
    printf("%c", d);
    d++;
  }
  printf("\n");
  return 0;
}
