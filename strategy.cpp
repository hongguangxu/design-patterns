#include<iostream>
#include<string>
using namespace std;

//class Compositor;
class Compositor
{
public:
    virtual int Compose(int) = 0;
protected:
    Compositor();
};

Compositor::Compositor()
{

}

class Composition 
{
public:
    Composition(Compositor*);
    void Repair(int);
private:
    Compositor* _compositor;
};
Composition::Composition(Compositor* com)
{
    _compositor = com;
}

void Composition::Repair(int v)
{
    _compositor->Compose(v);
}


class SimpleCompositor : public Compositor
{
public:
    SimpleCompositor();
    virtual int Compose(int);
};

SimpleCompositor::SimpleCompositor()
{

}
int SimpleCompositor::Compose(int a)
{
    cout << "simple compositor " << a << endl;
}

class TextCompositor : public Compositor
{
public:
    TextCompositor();
    virtual int Compose(int);
};

TextCompositor::TextCompositor()
{

}
int TextCompositor::Compose(int b)
{
    cout << "text compositor " << b << endl;
}

int main()
{
    Composition *A = new Composition(new SimpleCompositor);
    A->Repair(10);
    A = new Composition(new TextCompositor);
    A->Repair(20);
    return 0;
}
