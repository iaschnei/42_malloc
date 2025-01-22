#include "libft_malloc/libft_malloc.h"
int printf(const char *format, ...);

// export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

int main(void) {

  int *ptr = (int *)malloc(sizeof(int));
  if (ptr == NULL) {
    return (1);
  }
  
  *ptr = 42;
  printf("%d\n", *ptr);

  int *ptr2 = (int *)malloc(sizeof(int));
  if (ptr2 == NULL) {
    return (1);
  }

  *ptr = 43;
  printf("%d\n", *ptr2);
}
