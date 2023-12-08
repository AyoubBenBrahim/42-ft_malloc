#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *ptr1 = (char *)malloc(10);
  memset(ptr1, 'A', 10);

  char *ptr2 = (char *)malloc(15);
  memset(ptr2, 'B', 15);

  char *ptr3 = (char *)malloc(20);
  memset(ptr3, 'C', 20);


  free(ptr1);
  free(ptr2);
  free(ptr3);

  return 0;
}
