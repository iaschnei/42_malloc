#include "libft_malloc/libft_malloc.h"
#include "libft/libft.h"
#include <assert.h>
int printf(const char *format, ...);
int strcmp(const char *s1, const char *s2);

// export LD_LIBRARY_PATH=./libft_malloc:$LD_LIBRARY_PATH

int main(void) {

  printf("------ SMALL ALLOCS : ------\n");
  
  int *int_ptr = malloc(sizeof(int));

  *int_ptr = 42;

  assert(*int_ptr==42);
  printf("int *  -> 42        = %d\n", *int_ptr);

  char *char_ptr = malloc(sizeof(char));

  *char_ptr = 'c';

  assert(*char_ptr=='c');
  printf("char * -> 'c'       = %c\n", *char_ptr);

  char *str_ptr = malloc(sizeof(char) * 6);

  str_ptr = "Hello";

  assert(strcmp(str_ptr, "Hello") == 0);
  printf("char * -> 'Hello'   = %s\n", str_ptr);

}
