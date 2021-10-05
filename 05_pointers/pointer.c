#include <stdio.h>

int main() {
  char c = 'a';
  int i = 5;
  long l = 9890;

  printf("Part 2:\n");
  printf("Char Address in Decimal: %lu\t in Hex: %x\n", &c, &c);
  printf("Int Address in Decimal: %lu\t in Hex: %x\n", &i, &i);
  printf("Long Address in Decimal: %lu\t in Hex: %x\n", &l, &l);

  char *cp = &c;
  int *ip = &i;
  long *lp = &l;

  printf("\nPart 4:\n");
  printf("Char Pointer: %c\n", *cp);
  printf("Int Pointer: %d\n", *ip);
  printf("Long Pointer: %ld\n", *lp);

  *cp = *cp + 1;
  *ip = *ip + 1;
  *lp = *lp + 1;

  printf("\nPart 5:\n");
  printf("Modified Char Pointer: %c\n", *cp);
  printf("Modified Int Pointer: %d\n", *ip);
  printf("Modified Long Pointer: %ld\n", *lp);

  unsigned int ui = 2020;
  int *uip = &ui;
  char *cip = &ui;

  printf("\nPart 7:\n");
  printf("Char Pointer: %p\t points to: %d\n", cip, *cip);
  printf("Int Pointer: %p\t points to: %d\n", uip, *uip);

  printf("\nPart 8:\n");
  printf("Unsigned Int in Decimal: %d\t in Hex: %x\n", ui, ui);

  printf("\nPart 9:\n");
  printf("Each byte: %hhu \t %hhu \t %hhu \t %hhu\n", *cip, *(cip+1), *(cip+2), *(cip+3));

  printf("\nPart 10:\n\n");
  char *copy = cip;
  for (int i = 1; i < 5; i++) {
    *copy = *copy + 1;
    printf("Pass %d: %hhu \t %hhu \t %hhu \t %hhu\n", i, *cip, *(cip+1), *(cip+2), *(cip+3));
    printf("Number in decimal: %d\t in hex: %x\n", ui, ui);
    copy++;
  }

  printf("\nPart 11:\n\n");
  copy = cip;
  for (int i = 1; i < 5; i++) {
    *copy = *copy + 16;
    printf("Pass %d: %hhu \t %hhu \t %hhu \t %hhu\n", i, *cip, *(cip+1), *(cip+2), *(cip+3));
    printf("Number in decimal: %d\t in hex: %x\n", ui, ui);
    copy++;
  }

  return 0;
}
