#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include <list>
using namespace std;

class Menu
{
public:
    // CTOR
    Menu();
    virtual ~Menu();
    Menu(const Menu& other);
    Menu& operator=(const Menu& other);
    // MISC
    Action Update();
    void Draw();
    void Push(Button *btn) {lst.push_back(btn);}

    protected:
private:
    list<Button*> lst;                             // list of menu objects
};

#endif // MENU_H
