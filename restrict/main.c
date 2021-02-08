#include <stdlib.h>
#include <stdio.h>

int foo(int * restrict p1, int * restrict p2) {
  *p1 = 2;
  *p2 = 3;
  return *p1 * (*p2);
}

int main(int argc, char **argv) {
  int *restrict p = malloc(sizeof(int));
  int *restrict t = p;

//  *p = 1, *q = 2;
  int ret = foo(p, t);
  printf("ret = %d\n", ret);
  return 0;
}
