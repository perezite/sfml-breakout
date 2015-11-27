#ifndef BLOCK_H
#define BLOCK_H

#include "Object.h"

enum Color
{
    yellow,
    green,
    blue
};

class Block : public Object
{
public:
    // CTOR & DTOR
    Block(int x, int y, int color);
    virtual ~Block();

    void Collision(Object *obj);
    void Update();

protected:
private:
};

#endif // BLOCK_H
