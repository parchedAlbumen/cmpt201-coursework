#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
  char *line = NULL;
  size_t size = 0;
  while (1) {
    printf("Enter programs to run.\n");
    ssize_t len = getline(&line, &size, stdin);
    if (len != -1) {
      line[len - 1] = '\0'; // for stripping
      pid_t pid = fork();
      if (pid != 0) {
        pid_t wait_pid = waitpid(pid, NULL, 0);
        if (wait_pid == -1) {
          printf("BAD, need pid\n");
        }
      } else {
        if (execl(line, line, NULL) == -1) {
          printf("Exec failure\n");
        }
      }
    } else {
      printf("GETLINE ERROR\n");
      exit(EXIT_FAILURE);
    }
  }
}
