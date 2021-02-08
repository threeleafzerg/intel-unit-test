#include <type_traits>
#include <iostream>
#include <utility>

struct A {
//	virtual void foo() {};
	A& operator=(const A& rhs) {}
};

struct B {
public:
	B() {};
//	B(const B& rhs) {};
//	B& operator=(const B& rhs) {};
//	const A val;
//	~B() {};
//	virtual void foo() {};
	A a;
};

int main() {
std::cout << std::boolalpha << std::is_trivially_copyable<B>() << std::endl;
std::cout << std::boolalpha << std::is_standard_layout<B>() << std::endl;
}

