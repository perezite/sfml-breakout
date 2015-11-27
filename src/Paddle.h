#ifndef PADDLE_H
#define PADDLE_H

#include "Object.h"


class Paddle : public Object
{
    public:
        // CTOR & DTOR
        Paddle(int x0, int y0);
        virtual ~Paddle();
        // MISC
        void OnKBInput(sf::Key::Code KeyCode);
        void Update();
        ObjectType GetType() { return paddle; }
    protected:
    private:
};

#endif // PADDLE_H
