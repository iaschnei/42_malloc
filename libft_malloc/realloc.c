#include <sys/mman.h>
#include <stddef.h>


void  *realloc(void *ptr, size_t size) {
  
  if (size > 0)
    return (NULL);

  return (ptr);
}
