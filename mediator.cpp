#include<iostream>
#include<cstring>

using namespace std;
class Widget;
class DialogDirector
{
public:
    virtual ~DialogDirector();
    virtual void ShowDialog();
    virtual void WidgetChanged(Widget*) = 0;
     virtual void CreateWidgets(Widget*, Widget*, Widget*) = 0;

protected:
    DialogDirector();
    //virtual void CreateWidgets(Widget*, Widget*, Widget*) = 0;
};
DialogDirector::~DialogDirector()
{

}
DialogDirector::DialogDirector()
{

}
void DialogDirector::ShowDialog()
{

}

class Widget
{
public:
    Widget(DialogDirector*);
    virtual void Changed();
    virtual void HandleMouse();

private:
    DialogDirector* _director;
};
Widget::Widget(DialogDirector* dir)
{
    _director = dir;
}
void Widget::HandleMouse()
{

}
void Widget::Changed()
{
    cout << "Changed............" << endl;
    _director->WidgetChanged(this);
}

class ListBox : public Widget
{
public:
    ListBox(DialogDirector*);
    virtual void HandleMouse();
};

ListBox::ListBox(DialogDirector* dir):Widget(dir)
{
    
}
void ListBox::HandleMouse()
{
    cout << "list box handle mouse" << endl;
    this->Changed();
}

class EntryField : public Widget
{
public:
    EntryField(DialogDirector*);
    virtual void HandleMouse();
};
EntryField::EntryField(DialogDirector* dir):Widget(dir)
{

}
void EntryField::HandleMouse()
{
    cout << "entry field handle mouse" << endl;
    this->Changed();
}

class Button : public Widget
{
public:
    Button(DialogDirector*);
    virtual void HandleMouse();
};
Button::Button(DialogDirector* dir):Widget(dir)
{

}
void Button::HandleMouse()
{
    cout << "button handle mouse" << endl;
    this->Changed();
}

class FontDialogDirector : public DialogDirector
{
public:
    FontDialogDirector();
    virtual ~FontDialogDirector();
    virtual void WidgetChanged(Widget*);
    virtual void CreateWidgets(Widget*, Widget*, Widget*);

protected:
    //virtual void CreateWidgets(Widget*, Widget*, Widget*);
    virtual void setButton(Widget*);
    virtual void setListBox(Widget*);
    virtual void setEntryField(Widget*);
private:
    Widget* _but;
    Widget* _lis;
    Widget* _enf;
};
FontDialogDirector::FontDialogDirector()
{

}
FontDialogDirector::~FontDialogDirector()
{

}
void FontDialogDirector::setButton(Widget* wid)
{
    _but = wid;
}
void FontDialogDirector::setListBox(Widget* wid)
{
    _lis = wid;
}
void FontDialogDirector::setEntryField(Widget* wid)
{
    _enf = wid;
}
void FontDialogDirector::CreateWidgets(Widget* b, Widget* l, Widget* e)
{
    setButton(b);
    setListBox(l);
    setEntryField(e);   
}
void FontDialogDirector::WidgetChanged(Widget* wid)
{
    cout << "wid changed" << endl;
    if(wid == this->_but)
        cout << "button OP" << endl;
    else if(wid == this->_lis)
        cout << "list OP" << endl;
    else if(wid == _enf)
        cout << "entry OP" << endl;
    return;
}

int main()
{
    DialogDirector *dire = new FontDialogDirector;
    Widget* button = new Button(dire);
    Widget* lisb = new ListBox(dire);
    Widget* enf = new EntryField(dire);
    dire->CreateWidgets(button, lisb, enf);
    button->HandleMouse();
    lisb->HandleMouse();
    enf->HandleMouse();
    return 0;
}

