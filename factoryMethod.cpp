#include<iostream>

using namespace std;
class Product
{
public:
    Product();
    virtual ~Product();
    virtual void foo() = 0;
    virtual void bar() = 0;
};
Product::Product()
{

}

Product::~Product()
{
    cout << "~Product" << endl;
}

class MyProduct : public Product
{
public:
    virtual void foo();
    virtual void bar();
};
void MyProduct::foo()
{
    cout << "my product foo" << endl;
}
void MyProduct::bar()
{
    cout << "your product bar" << endl;
}

class YourProduct : public Product
{
public:
    virtual void foo();
    virtual void bar();
};
void YourProduct::foo()
{
    cout << "your product foo" << endl;
}

void YourProduct::bar()
{
    cout << "your product bar" << endl;
}

class Creator
{
public:
    virtual Product* Create(int);
};

Product* Creator::Create(int id)
{
    if(id == 0)
        return new MyProduct;
    else if(id == 1)
        return new YourProduct;
    return 0;
}

int main()
{
    Creator *c = new Creator;
    Product *p1 = c->Create(0);
    p1->foo();
    Product *p2 = c->Create(1);
    p2->bar();
    delete c;
    return 0;
}
