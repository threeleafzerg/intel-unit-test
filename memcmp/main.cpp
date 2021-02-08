#include <string.h>
#include <stdio.h>

void print_address(char &v, char *start) {
  char *addr = &v;
  printf("offset = %d\n", addr - start);
  printf("start = %p\n", start);
  printf("v addr = %p\n", &v);
}

int main(int argc, char **argv) {
#if 0
  float f;

  int a = 0xbcbcbcbc;

  *reinterpret_cast<int *>(&f) = a;

  int ret = memcmp(&f, &a, sizeof(float));

  printf("ret = %d\n", ret);
#endif 

  char a[10] = {0};

  char *start = (char *)a;

  print_address(a[3], start);

  return 0;
}
