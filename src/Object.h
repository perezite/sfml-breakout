#ifndef __OBJECT_H
#define __OBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;

// structure for the status of an object
enum ObjectState
{
running,
dying,
deletion  // object is expected to be deleted
};

// structure for the type of an object
enum ObjectType
{
unknown = 0,
paddle = 1,
ball = 2
};

class Object
{
public:
    // CTOR
    Object() {};
    Object(string image_path);

    // SET
    void SetX(float _x)  {sprite.SetX(_x); }
    void SetY(float _y)  {sprite.SetY(_y);}
    void Move(float dx, float dy) {sprite.Move(dx, dy);}
    void SetSprite(string image_path);
    virtual void SetState(int state) {m_state = state;}

    // GET
    float GetX()  {return sprite.GetPosition().x;}
    float GetY()  {return sprite.GetPosition().y;}
    float GetWidth() {return sprite.GetSize().x;}
    float GetHeight() {return sprite.GetSize().y;}
    sf::Sprite *GetSprite(void) {return &sprite;}
    virtual int GetState(void) {return m_state;}

    // MISC
    virtual void Update() {}
    virtual void Collision(Object *obj) {}
    void DispatchKBInput(sf::Key::Code KeyCode);
    virtual void OnKBInput(sf::Key::Code KeyCode) {}
    virtual ObjectType GetType() {return unknown;}
private:

    sf::Image image;
    sf::Sprite sprite;          // Contains positions x, y
    int m_state;
};

#endif

