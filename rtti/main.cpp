#include <iostream>
#include <typeinfo>
using namespace std;

struct Base {
    virtual ~Base() {}
};
 
struct D1: Base {
    virtual void name() {}
};
 
struct D2: Base {
    virtual void name() {}
};

int main()
{
    Base* b1 = new Base;
    if(D1* d = dynamic_cast<D1*>(b1))
    {
        std::cout << "downcast from b1 to d successful\n";
        d->name(); // safe to call
    }
 
    Base* b2 = new D2;
		D2* pd1 = dynamic_cast<D2*>(b2);
    if(pd1 != NULL)
    {
        std::cout << "downcast from b2 to d2 successful\n";
        pd1->name(); // safe to call
    }

		D1* pd2 = dynamic_cast<D1*>(b2);
#if 0
    if(D1* d = dynamic_cast<D1*>(b2))
    {
        std::cout << "downcast from b2 to d2 successful\n";
        d->name(); // safe to call
    }
#endif 
		std::cout << typeid(b2).name() << std::endl;
		std::cout << typeid(*b2).name() << std::endl;

    delete b1;
    delete b2;
		return 0;
}
