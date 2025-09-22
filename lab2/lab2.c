#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;
  ssize_t size;

  while (1) {
    printf("Enter program to run: ");
    size = getline(&line, &len, stdin);
    if (size == -1) {
      perror("getline");
      free(line);
      return 1;
    }

    if (line[size - 1] == '\n') {
      line[size - 1] = '\0';
    }

    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      free(line);
      return 1;
    }

    if (pid == 0) {
      execl(line, line, (char *)NULL);
      perror("execl");
      exit(1);
    } else {
      int status;
      waitpid(pid, &status, 0);
    }

    free(line);
  }
}
