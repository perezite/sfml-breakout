#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;

enum ButtonState
{
unselect,
select,
onclick
};

enum Action
{
    none,
    start,
    quit
};

class Button
{
public:
    // CTOR
    Button() {m_state = unselect;}
    Button(string unselect_path);
    virtual ~Button();
    Button(const Button& other);
    Button& operator=(const Button& other);
    // SET
    void SetX(float _x)  {sprite.SetX(_x); }
    void SetY(float _y)  {sprite.SetY(_y);}
    void SetSelectImage(string path);
    void SetUnselectImage(string path);
    void SetAction(Action a) {m_action = a;}
    // GET
    float GetX()  {return sprite.GetPosition().x;}
    float GetY()  {return sprite.GetPosition().y;}
    float GetWidth() {return sprite.GetSize().x;}
    float GetHeight() {return sprite.GetSize().y;}
    sf::Sprite *GetSprite(void) {return &sprite;}
    int GetButtonState() {return m_state;}
    Action GetAction() {return m_action;}
    // MISC
    void ToggleSelect();
    void ToggleUnselect();
    void ToggleOnClick();
    void Update();
private:
    sf::Image image_select;
    sf::Image image_unselect;
    sf::Sprite sprite;          // Contains positions x, y
    ButtonState m_state;
    Action m_action;            // Action that the button performs
};

#endif // BUTTON_H
