#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <sys/mman.h>
# include <stddef.h>

# define ALIGNMENT 8  // linux requires 8 bytes alignment
# define ALIGN(size)  (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
# define HEADER_SIZE  (ALIGN(sizeof(size_t)))
# define FOOTER_SIZE  (ALIGN(sizeof(size_t)))

# define SMALL  64
# define MEDIUM 4096
# define SMALL_AREA_SIZE   (sysconf(_SC_PAGESIZE) * 5) // 64 * 100 + 64 * 200 (headers and footers)
# define MEDIUM_AREA_SIZE  (sysconf(_SC_PAGESIZE) * 105) // 4096 * 100 + 64 * 200


typedef struct s_area {
  void    *memory;
  size_t  size;
  size_t  available_size;
  size_t  num_blocks;
} t_area;

typedef struct s_areas_manager {
  t_area  *small_areas;
  size_t  num_small_areas;
  t_area  *medium_areas;
  size_t  num_medium_areas;
  t_area  *large_areas;
  size_t  num_large_areas;
} t_areas_manager;

// Global variable 1 : allocations manager
extern t_areas_manager areas_manager;

// ---------------- MALLOC ---------------------------

void  *malloc(size_t size);

// ---------------- FREE -----------------------------

void  free(void *ptr);

// ---------------- REALLOC --------------------------

void  *realloc(void *ptr, size_t size);

// ---------------- SHOW_MEM -------------------------

void  show_alloc_mem();

void  show_alloc_mem_ex();

#endif
