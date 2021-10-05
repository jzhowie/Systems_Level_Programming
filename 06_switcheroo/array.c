#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int a[10];
  a[0] = 0;
  int i;
  srand(time(NULL));
  printf("[");
  for (i = 0; i < 10; i++) {
    if (i != 0) a[i] = rand();
    if (i != 9) printf("%d, ", a[i]);
    else printf("%d", a[i]);
  }
  printf("]\n");

  int b[10];
  int *pointer_A = a + 9;
  int *pointer_B = b;

  printf("[");
  for (i = 0; i < 10; i++) {
    *pointer_B = *pointer_A;
    if (i != 9) printf("%d, ", *pointer_B);
    else printf("%d", *pointer_B);
    pointer_B++;
    pointer_A--;
  }
  printf("]\n");

  // printf("[");
  // for (i = 0; i < 10; i++) {
  //   pointer_B[i] = pointer_A[9 - i];
  //   if (i != 9) printf("%d, ", pointer_B[i]);
  //   else printf("%d", pointer_B[i]);
  // }
  // printf("]\n");
  return 0;
}
