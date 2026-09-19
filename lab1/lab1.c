#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("hello world!!!\n");
  printf("enter something here:");
  char *sentence = NULL;
  size_t len = 0;
  ssize_t num_char = getline(&sentence, &len, stdin);
  printf("%s", sentence);
  free(sentence);
}
