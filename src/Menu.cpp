#include "Menu.h"
#include "Framework.h"

Menu::Menu()
{
    Button *button;
    button = new Button("datas/button_start_unselect.png");
    button->SetSelectImage("datas/button_start_select.png");
    button->SetX(100);
    button->SetY(100);
    button->SetAction(start);
    Push(button);
    button = new Button("datas/button_quit_unselect.png");
    button->SetSelectImage("datas/button_quit_select.png");
    button->SetX(100);
    button->SetY(150);
    button->SetAction(quit);
    Push(button);
}

Menu::~Menu()
{
    //dtor
}

Menu::Menu(const Menu& other)
{
    //copy ctor
}

Menu& Menu::operator=(const Menu& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void Menu::Draw()
{
    sf::RenderWindow *App = GetApp();
    list<Button*>::iterator it;

    for (it=lst.begin() ; it != lst.end(); it++ )
    {
        App->Draw(*((*it)->GetSprite()));
    }
}

// helper function: Perform action according to Menu Input
void PerformAction(Action action)
{
    if(action == start)
    {
        SetProgramState(loadgamecore);
    }
    if(action == quit)
    {
        SetProgramState(closing);
    }
}

Action Menu::Update()
{
    list<Button*>::iterator it;

    // Update
    for (it=lst.begin() ; it != lst.end(); it++ )
    {
        (*it)->Update();
    }

    // Check for Clicks
    for (it=lst.begin() ; it != lst.end(); it++ )
    {
        int state = (*it)->GetButtonState();
        if(state == onclick)
        {
            Action action = (*it)->GetAction();
            cout << "clicked button with action " << action << endl;
            PerformAction(action);
            return action;              // assume, that only one button can be clicked at once

        }
    }

}

