#include "../libft/libft.h"
#include "libft_malloc.h"
#include <stdbool.h>

void  free(void *ptr) {

  // Mark a block as free 
  // If applicable, coalesce the freed blocks
  // If area is now empty, free it with munmap and set the variable in manager to null
  // If areas from the manager is empty, free it too
  //
  if(ptr == NULL)
    return;

  size_t *header = (size_t *)((char *)ptr - HEADER_SIZE);

  // If area is already freed
  if (!(*header & 1))
    return;

  t_area *current_areas;
  size_t  num_of_areas;

  if (*header - HEADER_SIZE - FOOTER_SIZE <= SMALL) {
    current_areas = areas_manager.small_areas;
    num_of_areas = areas_manager.num_small_areas;
  } else if (*header - HEADER_SIZE - FOOTER_SIZE <= MEDIUM) {
    current_areas = areas_manager.medium_areas;
    num_of_areas = areas_manager.num_medium_areas;
  } else {
    current_areas = areas_manager.large_areas;
    num_of_areas = areas_manager.num_large_areas;
  }

  *header = *header & ~1L; // Mark the block as free, clearing the least significant bit
  
  size_t *next_header = header + *header;
  if (next_header && !(*next_header & 1)) {
    *header += *next_header;  // Add next's block size
  }


  // Find out if we need to check for the previous block too
  bool first_block = false;

  for (int i = 0; i < num_of_areas; i++) {
    if (header == current_areas[i].memory)
       first_block = true;
  }
  
  if (first_block == false) { 
    size_t *prev_header = header - *(header - FOOTER_SIZE) + HEADER_SIZE;
    if (!(*prev_header & 1)) {
      *prev_header += *header;  // Add previous' block size
      header = prev_header;
    }
  }


  // TODO :
  //
  // -- For small and medium
  // 
  // - Decrease num_of_blocks and increase available size of the area
  //    Note : only decrease the available size of the original area BEFORE coalesce
  // - Check if we can unmap the area : must be the only block left
  //    -> first block should be true (? check for edg cases)
  //    -> num_of_blocks of the area should be 1
  // - Decrease number of areas if applicable
  // - If it was the last area of this size, set current_area to NULL  
  // 
  // -- For large
  //
  // - Unmap the zone and decrease num of areas
  // - Check if it was the last large area, if so, set large_areas to NULL
  
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
