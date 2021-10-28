#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
  int arr[10];
  int i;
  int random = open("/dev/random", O_RDONLY);
  if (random == -1) {
    printf("%s\n", strerror(errno));
    return 0;
  }
  if (read(random, arr, sizeof(arr)) == -1) {
    printf("%s\n", strerror(errno));
    return 0;
  }

  printf("Printing random array: \n");
  for (i = 0; i < 10; i++) {
    printf("element %d: %d\n", i, arr[i]);
  }

  int arr2[10];
  int random2 = open("randomarr.txt", O_RDWR);
  if (random2 == -1) {
    printf("%s\n", strerror(errno));
    return 0;
  }
  if (write(random2, arr, sizeof(arr)) == -1) {
    printf("%s\n", strerror(errno));
    return 0;
  }

  printf("\nWriting to file...\n");

  if (read(random2, arr2, sizeof(arr2)) == -1) {
    printf("%s\n", strerror(errno));
    return 0;
  }
  printf("Reading from file...\n");

  printf("Printing copied array: \n");
  for (i = 12; i < 22; i++) {
    printf("element %d: %d\n", i - 12, arr2[i]);
  }

  return 0;
}
