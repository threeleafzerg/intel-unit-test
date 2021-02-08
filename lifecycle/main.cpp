#include <iostream>
#include <stdlib.h>
class A {
public:
  A() { std::cout << "A ctor!" << std::endl; };
  void foo() { std::cout << "A::foo" << std::endl; };
  ~A() { std::cout << "A dtor!" << std::endl; };
};


void at_exit_callback(void) {
  std::cout << "at exit callback" << std::endl;
}

void func() {
  static thread_local A a;
  a.foo();
}

static thread_local A a;

int main(int argc, char **argv) {
  atexit(at_exit_callback);  
  func();
  return 0;
}

