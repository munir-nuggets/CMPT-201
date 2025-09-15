#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *line = NULL;
  size_t len = 0;

  ssize_t size = getline(&line, &len, stdin);
  if (size == -1) {
    perror("error reading file");
  }

  char *saveptr;
  char *token = strtok_r(line, " ", &saveptr);
  while (token != NULL) {
    printf("%s\n", token);
    token = strtok_r(NULL, " ", &saveptr);
  }

  free(line);
  return 0;
}
