#include<iostream>
#include<cstring>
using namespace std;

class TCPState;
class TCPClosed;
//class TCPOctetStream;
class TCPConnection 
{
public:
    TCPConnection();
    void ActiveOpen();
    void PassiveOpen();
    void Close();
    void Send();
    void Acknowledge();
    void Synchronize();
    //void ProcessOctet(TCPOctetStream*);
protected:
    friend class TCPState;
    void ChangeState(TCPState*);
private:
    TCPState* _state;
};


class TCPState 
{
public:
    virtual void Transit(TCPConnection*);
    virtual void ActiveOpen(TCPConnection*);
    virtual void PassiveOpen(TCPConnection*);
    virtual void Close(TCPConnection*);
    virtual void Synchronize(TCPConnection*);
    virtual void Acknowledge(TCPConnection*);
    virtual void Send(TCPConnection*);
protected:
    void ChangeState(TCPConnection*, TCPState*);
};

void TCPState::Transit(TCPConnection*) { }
void TCPState::ActiveOpen(TCPConnection*) { }
void TCPState::PassiveOpen(TCPConnection*) { }
void TCPState::Close(TCPConnection*) { }
void TCPState::Synchronize(TCPConnection*) { }
void TCPState::Acknowledge(TCPConnection*) { }
void TCPState::Send(TCPConnection*) { }
void TCPState::ChangeState(TCPConnection* t, TCPState* s) 
{ 
    t->ChangeState(s);
}


void TCPConnection::ChangeState(TCPState* s)
{
    _state = s;
}

void TCPConnection::ActiveOpen()
{
    cout << "active open" << endl;
    _state->ActiveOpen(this);
}

void TCPConnection::PassiveOpen()
{
    cout << "Passive open" << endl;
    _state->PassiveOpen(this);
}

void TCPConnection::Close()
{
    cout << "tcp close" << endl;
    _state->Close(this);
}

void TCPConnection::Acknowledge()
{
    cout << "ack" << endl;
    _state->Acknowledge(this);
}

void TCPConnection::Synchronize()
{
    cout << "syn" << endl;
    _state->Synchronize(this);
}
class TCPEstablished : public TCPState
{
public:
    TCPEstablished() { }
    ~TCPEstablished() { }
    static TCPState* Instance()
    {
        TCPState* tcp = new TCPEstablished;
        return tcp; 
    }
    //static void Instance() { }
    virtual void Transit(TCPConnection*);
    virtual void Close(TCPConnection*);
};

class TCPListen : public TCPState
{
public:
    TCPListen() { }
    ~TCPListen() { }
    static TCPState* Instance()
    {
        TCPState* tcp = new TCPListen;
        return tcp; 
    }
    virtual void Send(TCPConnection*);
};

class TCPClosed : public TCPState
{
public:
    TCPClosed() { }
    ~TCPClosed() { }
    static TCPState* Instance()
    {
        TCPState* tcp = new TCPClosed;
        return tcp; 
    }
    virtual void ActiveOpen(TCPConnection*);
    virtual void PassiveOpen(TCPConnection*);
};
void TCPEstablished::Close(TCPConnection* t)
{
    cout << "close->listen" << endl;
    ChangeState(t, TCPListen::Instance());
}
void TCPEstablished::Transit(TCPConnection*t)
{
    
}
void TCPListen::Send(TCPConnection* t)
{
    cout << "send->establish" << endl;
    ChangeState(t, TCPEstablished::Instance());
}
void TCPClosed::ActiveOpen(TCPConnection* t)
{
    cout << "close -> activeOPEN" << endl;
    ChangeState(t, TCPEstablished::Instance());
}

void TCPClosed::PassiveOpen(TCPConnection* t)
{
    ChangeState(t, TCPListen::Instance());
}

TCPConnection::TCPConnection()
{
    _state = TCPClosed::Instance();
    cout << "init tcp" << endl;
}
int main()
{
    TCPConnection* tcp = new TCPConnection;
    tcp->ActiveOpen();
    tcp->Close();
    cout << "end" << endl;
    return 0;
}

