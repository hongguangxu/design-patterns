#include<iostream>
#include<list>
#include<string>
#include<cstring>

using namespace std;

class Document
{
public:
    Document(char *s);
    ~Document();
    void Open();
    void Close();
    void Cut();
    void Copy();
    void Paste();
private:
    char s[10];
};
Document::Document(char* name)
{
    if(s != NULL)
        strncpy(s, name, strlen(name)+1);
}
Document::~Document()
{
    memset(s, 0, 10);
}
void Document::Open()
{
    cout << "Open file: " << s << endl;
    return;
}
void Document::Close()
{
    cout << "Close file: " << s << endl;
}
void Document::Cut()
{
    cout << "Cut file: " << s << endl;
}
void Document::Copy()
{
    cout << "Copy file: " << s << endl;
}
void Document::Paste()
{
    cout << "Paste file: " << s << endl;
}

class Application {
public:     
    Application();
    ~Application();
    void Add(Document*);
    void Remove(Document*);
private:
    list<Document*> _docs;
};
Application::Application()
{
    
}
Application::~Application()
{

}
void Application::Add(Document* doc)
{
    _docs.push_back(doc);
}
void Application::Remove(Document* doc)
{
    _docs.remove(doc);
}

class Command
{
public:
    virtual ~Command();
    //virtual const char* AskUser() = 0;
    virtual void Execute() = 0;
protected:
    //virtual const char* AskUser() = 0;
    //virtual void Execute() = 0;
    Command();
};
Command::Command()
{

}
Command::~Command()
{

}
class OpenCommand : public Command
{
public:
    OpenCommand(Application*);
    virtual void Execute();
protected:
    virtual void AskUser(char *);
private:
    Application* _application;
};

void OpenCommand::AskUser(char *str)
{
    cin.getline(str, 10);
    cout << "AskUser" << str << endl;
    return;
}
OpenCommand::OpenCommand(Application* app)
{
    _application = app;
}
void OpenCommand::Execute()
{
    char name[10] = {0};
    AskUser(name);
    if(name != NULL)
    {
        Document* document = new Document(name);
        _application->Add(document);
        document->Open();
    }
}

class PasteCommand : public Command
{
public:
    PasteCommand(Document*);
    virtual void Execute();
private:
    Document* _document;
};

PasteCommand::PasteCommand(Document* doc)
{
    _document = doc;
}

void PasteCommand::Execute()
{
    _document->Paste();
}

class MacroCommand : public Command 
{
public:
    MacroCommand();
    virtual ~MacroCommand();
    virtual void Add(Command*);
    virtual void Remove(Command*);
    virtual void Execute();
private:
    list<Command*> _cmds;
};
MacroCommand::MacroCommand()
{

}
MacroCommand::~MacroCommand()
{

}
void MacroCommand::Execute()
{
    for(list<Command*>::iterator i = _cmds.begin(); i != _cmds.end(); i++)
    {
        (*i)->Execute();
    }
}
void MacroCommand::Add(Command* c)
{
    _cmds.push_back(c);
}
void MacroCommand::Remove(Command* c)
{
    _cmds.remove(c);
}
int main()
{
    Application *apl = new Application;
    OpenCommand *opcmd = new OpenCommand(apl);
    MacroCommand *Mcmd = new MacroCommand;
    char name[] = "xuhg";
    Document* doc = new Document(name);
    PasteCommand *pcmd = new PasteCommand(doc);
    Mcmd->Add(opcmd);
    Mcmd->Add(pcmd);
    Mcmd->Execute();
    Mcmd->Remove(opcmd);
    Mcmd->Remove(pcmd);
    return 0;
}
