#include <sys/mman.h>
#include <stddef.h>

void  *malloc(size_t size) {

  void *allocated_space;

  allocated_space = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  return (allocated_space);
}
