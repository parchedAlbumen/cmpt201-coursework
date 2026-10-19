#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  if (free_list_ptr->size >= size) {
    return free_list_ptr->id;
  }
  while (1) {
    if (free_list_ptr->next == NULL) {
      return -1;
    }

    free_list_ptr = free_list_ptr->next;
    if (free_list_ptr->size >= size) {
      return free_list_ptr->id;
    }
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t best_size = -1;
  if (free_list_ptr->size >= size) {
    best_size = free_list_ptr->size;
    best_fit_id = free_list_ptr->id;
  }

  while (free_list_ptr->next != NULL) {
    free_list_ptr = free_list_ptr->next;
    if (free_list_ptr->size >= size && free_list_ptr->size < best_size) {
      best_size = free_list_ptr->size;
      best_fit_id = free_list_ptr->id;
    }
  }

  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  uint64_t worst_size = 0;
  int worst_fit_id = -1;
  if (free_list_ptr->size >= size) {
    worst_size = free_list_ptr->size;
    worst_fit_id = free_list_ptr->id;
  }

  while (free_list_ptr->next != NULL) {
    free_list_ptr = free_list_ptr->next;
    if (free_list_ptr->size >= size && free_list_ptr->size > worst_size) {
      worst_size = free_list_ptr->size;
      worst_fit_id = free_list_ptr->id;
    }
  }
  return worst_fit_id;
}

int main(void) {
  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("ID for FIRST FIT is: %d\n", first_fit_id);
  printf("ID for BEST FIT is: %d\n", best_fit_id);
  printf("ID for WORST FIT is: %d\n", worst_fit_id);

  return 0;
}

/**
 *
 *      for part 2:
 *
 *      if free is empty:
 *          head = address of that free block
 *          head->next = null
 *      else:
 *        find the newest free block
 *
 *        if block before it (next to it) is free as well
 *          then merge
 *        if block after it (next to it) is free as well
 *          then merge
 *        else:
 *          add to newest block to the list
 *
 *
 */
