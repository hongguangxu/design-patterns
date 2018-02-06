#include<iostream>
#include<cstring>
#include<list>

using namespace std;
class Singleton;
class NameSingletonPair
{
public:
    NameSingletonPair(const char*, Singleton*);
    ~NameSingletonPair();
    void getSingletonName(char*);
    Singleton* getSingleton();
private:
    char _name[20];
    Singleton* _singleton;
};
void NameSingletonPair::getSingletonName(char* dstName)
{
    strcpy(dstName, _name);
}
Singleton* NameSingletonPair::getSingleton()
{
    return this->_singleton;
}

NameSingletonPair::NameSingletonPair(const char* name, Singleton* singleton)
{
    //if(name == NULL || singleton == NULL)
    strcpy(_name, name);
    _singleton = singleton;
}
class Singleton
{
public:
    static void Register(const char*, Singleton*);
    static Singleton* Instance();
protected:
    Singleton* lookup(const char*);
private:
    static Singleton* _instance;
    static list<NameSingletonPair*> _register;
};
Singleton* Singleton::_instance = 0;
list<NameSingletonPair*> Singleton::_register;
Singleton* Singleton::Instance()
{
    if(_instance == 0)
    {
	cout << "create singleton instance" << endl;
	Singleton *singleton = new Singleton;
        const char* singletonName = "MySingleton";
	_instance = singleton->lookup(singletonName);
	//Singleton::_instance = temp;
	delete singleton;
    }
    return _instance;
}


Singleton* Singleton::lookup(const char* name)
{
    char tmpName[20] = {0}; 
    cout << "lookup my singleton" << endl;
    for(list<NameSingletonPair*>::iterator i = _register.begin(); i != _register.end(); i++)
    {
        (*i)->getSingletonName(tmpName);
        if(0==strcmp(name, tmpName))
        {
	    cout << "my singleton be found" << endl;
            return ((*i)->getSingleton());    
        }
    }
    return NULL;
}


void Singleton::Register(const char* name, Singleton* singleton)
{
    cout << "register my singleton" << endl;
    NameSingletonPair *nameSP = new NameSingletonPair(name, singleton);
    _register.push_back(nameSP);
}

class MySingleton : public Singleton
{
public:
    MySingleton();
    ~MySingleton();
};
MySingleton::MySingleton()
{
    Singleton::Register("MySingleton", this);
}
MySingleton::~MySingleton()
{

}

static MySingleton thisSinleton;
int main()
{
    Singleton::Instance();
    return 0;
}
