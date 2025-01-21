#include "../libft/libft.h"
#include "libft_malloc.h"
#include <stdint.h>
#include <sys/mman.h>

static void     *tiny_alloc(size_t size);
static void     *small_alloc(size_t size);
static void     *large_alloc(size_t size);
static t_area   init_area(size_t size);

t_areas_manager areas_manager = {NULL, 0, NULL, 0, NULL, 0};

void  *malloc(size_t size) {

  void  *allocated_space = NULL;

  size = ALIGN(size);   // Align size to 8 bytes

  if (size <= SMALL) {
    allocated_space = tiny_alloc(size);
  }
  else if (size > SMALL && size <= MEDIUM) {
    allocated_space = small_alloc(size);
  }
  else {
    allocated_space = large_alloc(size);
  }

  return (allocated_space);
}

static void *tiny_alloc(size_t size) {

  // Check if there is already a tiny area allocated
  // -> YES:
  //        Check if there is an available slot
  //        -> YES:
  //                Allocate the space for that alloc
  //        -> NO:
  //                Go back and allocate a new area
  // -> NO:
  //        Allocate a new area
  //
  //  Same logic for small_alloc
  
  if (areas_manager.small_areas == NULL) {
    areas_manager.small_areas[0] = init_area(SMALL_AREA_SIZE);
    if ((int64_t) areas_manager.small_areas[0].memory < 0) {
      write(2, "Fatal error: mmap failed\n", 25); 
      return (NULL);
    }
    areas_manager.num_small_areas = 1;
    return (malloc(size));
  }
  

  // Iterate over all areas to find the last one not full or just the last one full
  int i = 0;
  while (i < areas_manager.num_small_areas) {
    if (areas_manager.small_areas[i].num_blocks < 100) {
      break;
    }
    i++;
  }
  // If the last one is full too or if there isn't enough space anyway, we need to init another one
  if (areas_manager.small_areas[i].num_blocks >= 100 
      || areas_manager.small_areas[i].available_size < HEADER_SIZE + size + FOOTER_SIZE)
  {
    // FIXME : Can i do that ?
    areas_manager.small_areas[i + 1] = init_area(SMALL_AREA_SIZE);
    if ((int64_t) areas_manager.small_areas[0].memory < 0) {
      write(2, "Fatal error: mmap failed\n", 25); 
      return (NULL);
    }
    areas_manager.num_small_areas = 1;
    return (malloc(size));
  }

  size_t *cursor = areas_manager.small_areas[i].memory;

  while (*cursor != 0) { // && area is not free 
    cursor += *cursor;   // if the header does contain the size
  }

  // calculate block size with header + size (data) + footer
  // put that block size in header and footer for next / prev
  // if it is the first block, footer must be at 0 or smthg to stop
  // footer is used for free coalesce
  // increase area's block count, reduce available space
  // return the data segment of the block

  return (NULL);
}

static void *small_alloc(size_t size) {
  return (NULL);
}

static void *large_alloc(size_t size) {
  return (NULL);
}

static t_area init_area(size_t size) {
  t_area area;
  area.size = size;
  area.available_size = size;
  area.num_blocks = 0;
  area.memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  area.memory = ft_memset(area.memory, 0, size);
  return (area);
}
