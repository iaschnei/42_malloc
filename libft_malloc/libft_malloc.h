#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <sys/mman.h>
# include <stddef.h>

# define ALIGNMENT 8    // linux requires 8 bytes alignment
# define ALIGN(size)  (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
# define HEADER_SIZE  (ALIGN(sizeof(size_t)))

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
