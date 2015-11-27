#include "Block.h"
#include "Framework.h"


Block::Block(int x, int y, int color)
{
    // initialize sprite with correct color
    string filename;

    switch(color)
    {
    case yellow:
    {
        SetSprite("datas/block_yellow.png");
        break;
    }
    case blue:
    {
        SetSprite("datas/block_blue.png");
        break;
    }
    case green:
    {
        SetSprite("datas/block_green.png");
        break;
    }
    }

    // Rem: SetX() and SetY() manipulate the sprite, so
    // first initialize the sprite and then use SetX(), SetY()
    SetX(x);
    SetY(y);
}


void Block::Collision(Object *obj)
{
    this->SetState(deletion);
}

void Block::Update()
{
}

Block::~Block()
{
    //dtor
}
