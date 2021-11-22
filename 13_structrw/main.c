#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

#define FILE "population.data"

int main(int argc, char *argv[]) {
  if (argv[1] == NULL) {
    printf("No argument detected:\n");
    print_commands();
    return 0;
  }
  else if (strcmp(argv[1], "-read_csv") == 0) {
    read_csv();
  }
  else if (strcmp(argv[1], "-read_data") == 0) {
    read_data();
  }
  else if (strcmp(argv[1], "-add_data") == 0) {
    add_data();
  }
  else if (strcmp(argv[1], "-update_data") == 0) {
    update_data();
  }
  else {
    printf("Invalid argument detected:\n");
    print_commands();
  }
  return 0;
}

void read_csv() {
  int f = open("nyc_pop.csv", O_RDONLY);
  int nf = open(FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  struct pop_entry ma;
  strcpy(ma.boro, "Manhattan");
  struct pop_entry bk;
  strcpy(bk.boro, "Brooklyn");
  struct pop_entry qu;
  strcpy(qu.boro, "Queens");
  struct pop_entry bx;
  strcpy(bx.boro, "Bronx");
  struct pop_entry si;
  strcpy(si.boro, "Staten Island");
  int year;

  char line[100];
  lseek(f, 51, SEEK_SET);

  int lines = 0;
  for (lines = 0; lines < 23; lines++) {
    char a = '0';
    int count = 0;
    while (a != '\n') {
      read(f, &a, sizeof(a));
      count++;
    }
    lseek(f, -count, SEEK_CUR);
    read(f, line, count - 1);
    sscanf(line, "%d,%d,%d,%d,%d,%d", &year, &(ma.population), &(bk.population), &(qu.population), &(bx.population), &(si.population));
    ma.year = year;
    bk.year = year;
    qu.year = year;
    bx.year = year;
    si.year = year;
    write(nf, &ma, sizeof(ma));
    write(nf, &bk, sizeof(bk));
    write(nf, &qu, sizeof(qu));
    write(nf, &bx, sizeof(bx));
    write(nf, &si, sizeof(si));
    lseek(f, 1, SEEK_CUR);
  }
  close(f);
  close(nf);
  struct stat file;
  stat(FILE, &file);
  printf("Wrote %lld bytes to %s\n", file.st_size, FILE);
}

void read_data() {
  int f = open(FILE, O_RDONLY);
  struct stat file;
  stat(FILE, &file);
  int length = file.st_size / sizeof(struct pop_entry);
  struct pop_entry data[length];
  read(f, data, sizeof(data));
  int i;
  for (int i = 0; i < length; i++) {
    printf("%03d: %d\t Pop: %d\t Boro: %s\n", i+1, data[i].year, data[i].population, data[i].boro);
  }
  close(f);
}

void add_data() {
  struct pop_entry add;

  char buffer[20];
  char b[15];
  printf("Input year borough population:\n");
  fgets(buffer, sizeof(buffer) - 1, stdin);
  sscanf(buffer, "%d %s %d", &(add.year), b, &(add.population));

  int f = open(FILE, O_WRONLY | O_APPEND);
  strcpy(add.boro, b);
  write(f, &add, sizeof(add));
  close(f);
  printf("Appended data to file.\n");
}

void update_data() {
  read_data();
  struct pop_entry update;

  char buffer[20];
  int e;
  char b[15];
  printf("Enter entry number you want to update:\n");
  fgets(buffer, sizeof(buffer) - 1, stdin);
  sscanf(buffer, "%d", &e);
  printf("Updating entry %d:\n", e);
  printf("Input year borough population:\n");
  fgets(buffer, sizeof(buffer) - 1, stdin);
  sscanf(buffer, "%d %s %d", &(update.year), b, &(update.population));
  int f = open(FILE, O_WRONLY);
  lseek(f, (e-1)*sizeof(struct pop_entry), SEEK_SET);
  strcpy(update.boro, b);
  write(f, &update, sizeof(update));
  close(f);
  printf("File updated\n");
}

void print_commands() {
  printf("-read_csv to read data into a file\n");
  printf("-read_data to read data into an array\n");
  printf("-add_data to add data into a file\n");
  printf("-update_data to update data\n");
}
