
#include "libft_malloc.h"

void  free(void *ptr) {

  // Mark a block as free 
  // If applicable, coalesce the freed blocks
  // If area is now empty, free it with munmap and set the variable in manager to null
  // If areas from the manager is empty, free it too

  if(ptr == NULL)
    return;
}

// Kinda useful
/*
void traverse_blocks(size_t i) {
    size_t *cursor = areas_manager.small_areas[i].memory;

    // Forward traversal
    printf("Forward traversal:\n");
    while (*cursor != 0 && (*cursor & 1)) {
        printf("Block at %p, size: %zu\n", cursor, *cursor >> 1);
        cursor += *cursor >> 1;
    }

    // Backward traversal
    printf("Backward traversal:\n");
    while (cursor != areas_manager.small_areas[i].memory) {
        cursor -= (*cursor >> 1);
        printf("Block at %p, size: %zu\n", cursor, *cursor >> 1);
    }
}
*/
