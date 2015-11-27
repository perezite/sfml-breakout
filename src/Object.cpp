#include "Object.h"
#include <iostream>
#include "Framework.h"

Object::Object(string image_path)
{
    SetSprite(image_path);
}

// use this within the Update() function in order to handle certain
// input functions.
// One can also dispatch the KeyCodes manually to OnKBInput
void Object::DispatchKBInput(sf::Key::Code KeyCode)
{
    if(GetApp()->GetInput().IsKeyDown(KeyCode))
    {
        OnKBInput(KeyCode);
    }
}

void Object::SetSprite(string image_path)
{
    if(!image.LoadFromFile(image_path))
    {
        std::cout << "error";
    }

    sprite.SetImage(image);
    sprite.SetX(0.0);
    sprite.SetY(0.0);
}
