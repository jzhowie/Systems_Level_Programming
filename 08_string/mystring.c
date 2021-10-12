#include "mystring.h"

int mystrlen (char *s) {
  int length = 0;
  while (*s) {
    length++;
    s++;
  }
  return length;
}

char *mystrncpy (char *dest, char *source, int n) {
  int i;
  for (i = 0; i < n; i++) {
    dest[i] = source[i];
  }
  return dest;
}

char *mystrncat (char *dest, char *source, int n) {
  char *dest_temp = dest;
  while (*dest_temp) {
    dest_temp++;
  }

  int i;
  for (i = 0; i < n; i++) {
    dest_temp[i] = source[i];
  }
  return dest;
}

int mystrcmp (char *s1, char *s2) {
  char *s1_temp = s1;
  char *s2_temp = s2;
  while (*s1_temp || *s2_temp) {
    if (*s1_temp < *s2_temp) return -1;
    else if (*s1_temp > *s2_temp) return 1;
    else {
      s1_temp++;
      s2_temp++;
    }
  }
  return 0;
}

char *mystrchr (char *s, char c) {
  char *point;
  while (*s) {
    if (*s == c) {
      point = s;
      return point;
    }
    s++;
  }
  if (c == 0) {
    point = s;
    return point;
  }

  return 0;
}
