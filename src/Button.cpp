#include "Button.h"
#include "Framework.h"
#include <vector>
using namespace std;

Button::Button(string unselect_path)
{
    SetUnselectImage(unselect_path);
    ToggleUnselect();

}

Button::~Button()
{
    //dtor
}

Button::Button(const Button& other)
{
    //copy ctor
}

Button& Button::operator=(const Button& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void Button::SetUnselectImage(string path)
{
    if(!image_unselect.LoadFromFile(path))
    {
        std::cout << "error: couldn't load " << path << endl;
    }
}

void Button::SetSelectImage(string path)
{
    if(!image_select.LoadFromFile(path))
    {
        std::cout << "error";
    }
}

void Button::ToggleUnselect()
{
    sprite.SetImage(image_unselect);
    m_state = unselect;
}

void Button::ToggleSelect()
{
    sprite.SetImage(image_select);
    m_state = select;
}

void Button::ToggleOnClick()
{
    sprite.SetImage(image_select);
    m_state = onclick;
}

// return: vector containing information about what happened to the button
void Button::Update()
{
    sf::Window *App = GetApp();

    // Get mouse Input data from App
    float X = App->GetInput().GetMouseX();
    float Y = App->GetInput().GetMouseY();
    bool lclick = App->GetInput().IsMouseButtonDown(sf::Mouse::Left);
    bool rclick = App->GetInput().IsMouseButtonDown(sf::Mouse::Right);

    // Process Mouse hovering over button
    if(X < GetX() + GetWidth() and X > GetX() and
       Y < GetY() + GetHeight() and Y > GetY())
    {
        ToggleSelect();
    }
    else
    {
        ToggleUnselect();
    }

    // Process mouse click
    if(lclick  and X < GetX() + GetWidth() and X > GetX() and
       Y < GetY() + GetHeight() and Y > GetY())
    {
        ToggleOnClick();
    }
}

