#include<iostream>
#include<iterator>
#include<list>
using namespace std;

class Subject;
class Observer {
public:
    virtual ~Observer();
    virtual void Update(Subject* theChangedSubject) = 0;
protected:
    Observer();    
};
Observer::Observer()
{
    cout << "observer construct" << endl;
}
Observer::~Observer()
{
    cout << "observer destruct" << endl;
}
class Subject {
public:
    virtual ~Subject();
    virtual void Attach(Observer*);
    virtual void Detach(Observer*);
    virtual void Notify();
protected:
    Subject();
private:
    list<Observer*> _observers;
};

Subject::Subject()
{

}
Subject::~Subject()
{

}
void Subject::Attach(Observer* o)
{
    _observers.push_back(o);
}

void Subject::Detach(Observer* o)
{
    _observers.remove(o);
}

void Subject::Notify()
{
    list<Observer*>::iterator i;
    //ListIterator<Observer*> i(_observers);
    for (i = _observers.begin(); i != _observers.end(); i++)
    {
        //cout << " lll " << endl;
        (*i)->Update(this);
    }
}

class ClockTimer : public Subject 
{
public:
    ClockTimer();
 
    int GetHour();
    //virtual int GetMinute();
    //virtual int GetSecond();

    void Tick();
};
ClockTimer::ClockTimer()
{

}
int ClockTimer::GetHour()
{
    return 10;
}
void ClockTimer::Tick()
{
    // update internal time-keeping state
    Notify();
}

class DigitalClock: public Observer 
{
public:
    DigitalClock(ClockTimer*);
    virtual ~DigitalClock();
    
    virtual void Update(Subject*);

    virtual void Draw();

private:
    ClockTimer* _subject;
};

DigitalClock::DigitalClock (ClockTimer* s)
{
    _subject = s;
    _subject->Attach(this);
}

DigitalClock::~DigitalClock()
{
    _subject->Detach(this);
}

void DigitalClock::Update(Subject * theChangedSubject)
{
    if (theChangedSubject == _subject)
    {
        Draw();
    }
}

void DigitalClock::Draw()
{
    int hour = _subject->GetHour();
    cout << "digital clock hour: " << hour << endl;
    //int minute = _subject->GetMinute();
    //int second = _subject->GetSecond();
}

class AnalogClock: public Observer
{
public:
    AnalogClock(ClockTimer*);
    virtual ~AnalogClock();
    virtual void Update(Subject*);
    virtual void Draw();
private:
    ClockTimer* _subject;
};

AnalogClock::AnalogClock (ClockTimer *s)
{
    _subject = s;
    _subject->Attach(this);
}

AnalogClock::~AnalogClock()
{
    _subject->Detach(this);
}
void AnalogClock::Update(Subject * theChangedSubject)
{
    if(theChangedSubject == _subject)
    {
        Draw();
    }
}

void AnalogClock::Draw()
{
    int hour = _subject->GetHour();
    cout << "analog clock hour: " << hour << endl;
}

int main()
{
    ClockTimer* timer = new ClockTimer;
    DigitalClock* digitalClock = new DigitalClock(timer);
    AnalogClock* analogClock = new AnalogClock(timer);
    for(int i=0; i<5; i++)
    {
        timer->Tick();
    }
    delete digitalClock;
    delete analogClock;
    delete timer;
    return 0;
}
