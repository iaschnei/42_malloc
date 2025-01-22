#include "../libft/libft.h"
#include "libft_malloc.h"
#include <stdint.h>
#include <sys/mman.h>

static void     *small_alloc(size_t size);
static void     *medium_alloc(size_t size);
static void     *large_alloc(size_t size);
static t_area   init_area(size_t size);

t_areas_manager areas_manager = {NULL, 0, NULL, 0, NULL, 0};

void  *malloc(size_t size) {

  void  *allocated_space = NULL;

  size = ALIGN(size);   // Align size to 8 bytes

  if (size <= SMALL) {
    allocated_space = small_alloc(size);
  }
  else if (size > SMALL && size <= MEDIUM) {
    allocated_space = medium_alloc(size);
  }
  else {
    allocated_space = large_alloc(size);
  }

  return (allocated_space);
}


static void *small_alloc(size_t size) {

  if (areas_manager.small_areas == NULL) {
    areas_manager.small_areas = mmap(NULL, sizeof(t_area), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (areas_manager.small_areas == NULL) {
      write(2, "Fatal error: mmap failed\n", 25); 
      return (NULL);
    }
    areas_manager.small_areas[0] = init_area(SMALL_AREA_SIZE);
    if (areas_manager.small_areas[0].memory == NULL) {
      write(2, "Fatal error: mmap failed\n", 25); 
      return (NULL);
    }
    areas_manager.num_small_areas = 1;
    return (malloc(size));
  }
  
  // Iterate over all areas to find one with enough space (max 100 blocks)
  size_t i = 0;
  while (i < areas_manager.num_small_areas) {
    if (areas_manager.small_areas[i].num_blocks < 100 
       && areas_manager.small_areas[i].available_size >= size + HEADER_SIZE + FOOTER_SIZE) {
      break;
    }
    i++;
  }
  // If we reached the end with no sucess 
  if (i == areas_manager.num_small_areas)  {
    
    areas_manager.small_areas = realloc(areas_manager.small_areas, sizeof(t_area) * areas_manager.num_small_areas + 1);
    if (areas_manager.small_areas == NULL) {
      write(2, "Fatal error: mmap failed\n", 25);
      return (NULL);
    }
    areas_manager.small_areas[i] = init_area(SMALL_AREA_SIZE);
    if (areas_manager.small_areas[i].memory == NULL) {
      write(2, "Fatal error: mmap failed\n", 25); 
      return (NULL);
    }
    areas_manager.num_small_areas += 1;
    return (malloc(size));
  }

  size_t *cursor = areas_manager.small_areas[i].memory;

  while (*cursor != 0 && !(*cursor & 1)) { 
    cursor += *cursor >> 1; // Move to the next block, ignore lower bit
  }

  // Calculate total block size
  size_t block_size = ALIGN(HEADER_SIZE + size + FOOTER_SIZE);
  size_t *header = cursor;
  *header = block_size | 1; // Save the size and mark the block as allocated
  size_t *footer = cursor + (block_size >> 1) - 1;
  *footer = *header; 

  areas_manager.small_areas[i].num_blocks += 1;
  areas_manager.small_areas[i].available_size -= block_size;

  return (void *)(cursor + HEADER_SIZE);
}


static void *medium_alloc(size_t size) {

  if (areas_manager.medium_areas == NULL) {
    areas_manager.medium_areas = mmap(NULL, sizeof(t_area), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (areas_manager.medium_areas == NULL) {
      write(2, "Fatal error: mmap failed\n", 25); 
      return (NULL);
    }
    areas_manager.medium_areas[0] = init_area(MEDIUM_AREA_SIZE);
    if (areas_manager.medium_areas[0].memory == NULL) {
      write(2, "Fatal error: mmap failed\n", 25); 
      return (NULL);
    }
    areas_manager.num_medium_areas = 1;
    return (malloc(size));
  }
  
  // Iterate over all areas to find one with enough space (max 100 blocks)
  size_t i = 0;
  while (i < areas_manager.num_medium_areas) {
    if (areas_manager.medium_areas[i].num_blocks < 100 
       && areas_manager.medium_areas[i].available_size >= size + HEADER_SIZE + FOOTER_SIZE) {
      break;
    }
    i++;
  }
  // If we reached the end with no sucess 
  if (i == areas_manager.num_medium_areas)  {
    
    areas_manager.medium_areas = realloc(areas_manager.medium_areas, sizeof(t_area) * areas_manager.num_medium_areas + 1);
    if (areas_manager.medium_areas == NULL) {
      write(2, "Fatal error: mmap failed\n", 25);
      return (NULL);
    }
    areas_manager.medium_areas[i] = init_area(MEDIUM_AREA_SIZE);
    if (areas_manager.medium_areas[i].memory == NULL) {
      write(2, "Fatal error: mmap failed\n", 25); 
      return (NULL);
    }
    areas_manager.num_medium_areas += 1;
    return (malloc(size));
  }

  size_t *cursor = areas_manager.medium_areas[i].memory;

  while (*cursor != 0 && !(*cursor & 1)) { 
    cursor += *cursor >> 1; // Move to the next block, ignore lower bit
  }

  // Calculate total block size
  size_t block_size = ALIGN(HEADER_SIZE + size + FOOTER_SIZE);
  size_t *header = cursor;
  *header = block_size | 1; // Save the size and mark the block as allocated
  size_t *footer = cursor + (block_size >> 1) - 1;
  *footer = *header; 

  areas_manager.medium_areas[i].num_blocks += 1;
  areas_manager.medium_areas[i].available_size -= block_size;

  return (void *)(cursor + HEADER_SIZE);
}

static void *large_alloc(size_t size) {

  if (areas_manager.large_areas == NULL) {
    areas_manager.large_areas = mmap(NULL, sizeof(t_area), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (areas_manager.large_areas == NULL) {
      write(2, "Fatal error: mmap failed\n", 25);
      return (NULL);
    }
    areas_manager.large_areas[0] = init_area(size);
    if (areas_manager.large_areas[0].memory == NULL) {
      write(2, "Fatal error: mmap failed\n", 25);
      return (NULL);
    }
    areas_manager.num_large_areas = 1;
  }
  else {
    areas_manager.large_areas = realloc(areas_manager.large_areas, sizeof(t_area) * areas_manager.num_large_areas + 1);
    if (areas_manager.large_areas == NULL) {
      write(2, "Fatal error: mmap failed\n", 25);
      return (NULL);
    }
    areas_manager.large_areas[areas_manager.num_large_areas] = init_area(size);
    if (areas_manager.large_areas[areas_manager.num_large_areas].memory == NULL) {
      write(2, "Fatal error: mmap failed\n", 25);
      return (NULL);
    }
    areas_manager.num_large_areas += 1;
  }
  
  return (areas_manager.large_areas[areas_manager.num_large_areas - 1].memory);
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
