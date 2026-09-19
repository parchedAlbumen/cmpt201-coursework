#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("hello world!!!\n");
  printf("enter something here:");
  char *sentence = NULL;
  size_t len = 0;
  ssize_t num_char = getline(&sentence, &len, stdin);
  if (num_char == -1) {
    perror("getline failed!");
    exit(EXIT_FAILURE);
  }
  printf("%s\n", sentence);

  // is it supposed to be like this ?
  char *saveptr;
  char *ret = strtok_r(sentence, " ", &saveptr);
  while (ret != NULL) {
    printf("%s\n", ret);
    ret = strtok_r(NULL, " ", &saveptr);
  }
  free(sentence);
}
