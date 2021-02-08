#include <iostream>
#include <stdlib.h>
#include <pthread.h>



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

void *thread_func(void *arg)
{
  func();
  return NULL;
}

int main(int argc, char **argv) {
  atexit(at_exit_callback);  
  pthread_t tid;
  pthread_create(&tid, NULL, thread_func, NULL);
  pthread_join(tid, NULL); 
  return 0;
}

