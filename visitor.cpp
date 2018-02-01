#include<iostream>
#include<iterator>
#include<list>
using namespace std;
class ElementA;
class ElementB;
class CompositeElement;
class Visitor {
public:
    virtual void VisitElementA(ElementA*) = 0;
    virtual void VisitElementB(ElementB*) = 0;
    virtual void VisitCompositeElement(CompositeElement*) = 0;
protected:
    Visitor();
};

Visitor::Visitor()
{

}

class Element {
public:
    virtual ~Element();
    virtual void Accept(Visitor*) = 0;
protected:
    Element();
};
Element::Element()
{

}
Element::~Element()
{

}
class ElementA: public Element {
public:
    ElementA(){}
    virtual void Accept(Visitor* v)
    {
        v->VisitElementA(this);
    }
    void show()
    {
        cout << "aaaaa" << endl;
        return;
    }
};

class ElementB: public Element {
public:
    ElementB(){}
    virtual void Accept(Visitor* v)
    {
        v->VisitElementB(this);
    }
    void show()
    {
        cout << "bbbb" << endl;
        return;
    }
};

class CompositeElement: public Element {
public:
    virtual void Accept(Visitor*);
    void attach(Element* el)
    {
        _children.push_back(el);
    }
    void amount()
    {
        cout << "get sum" << endl;
    }
private:
    list<Element*> _children;
};

void CompositeElement::Accept (Visitor* v)
{
    list<Element*>::iterator i;
    for(i=_children.begin(); i != _children.end(); i++)
        (*i)->Accept(v);
}
class VisitorA: public Visitor {
public:
    void VisitElementA(ElementA* a)
    {
         a->show();
         return;
    }
    void VisitElementB(ElementB* b)
    {
         b->show();
         return;
    }
    void VisitCompositeElement(CompositeElement *cel)
    {
        cel->amount();
    }
};

int main()
{
     CompositeElement* comel = new CompositeElement;
     ElementA* A = new ElementA;
     ElementB* B = new ElementB;
     comel->attach(A);
     comel->attach(B);
     Visitor *vA = new VisitorA;
     comel->Accept(vA);
     vA->VisitCompositeElement(comel);
     //vA->VisitElementA(A);
    // vA->VisitElementB(B);
     return 0;
}
