#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

char *array[MAX];
int input_count = 0;

char *get_input() {
  char *line = NULL;
  size_t size = 0;
  printf("ENTER SOMETHING: ");
  ssize_t len = getline(&line, &size, stdin);
  if (len == -1) {
    exit(1);
  }

  line[len - 1] = '\0'; // for removing the newline of the inputs
  return line;
}

void add_input(char *input) {
  if (input_count >= MAX) {
    if (input_count > 0) {
      free(*array);
      for (int i = 1; i < input_count; i++) {
        array[i - 1] = array[i]; // move one index
      }
      input_count--;
    }
  }
  array[input_count] = input;
  input_count++;
}

void print_all_inputs() {
  for (int i = 0; i < input_count; i++) {
    printf("%s\n", array[i]);
  }
}

int main() {
  while (1) {
    char *input = get_input();
    add_input(input);
    if (strcmp(input, "print") == 0) {
      print_all_inputs();
    }
  }
  return 0;
}
