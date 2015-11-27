
#include "Object.h"

class Ball : public Object
{
public:
    // CTOR
    Ball();

    void Update();
    void Collision(Object *obj);
    ObjectType GetType() { return ball; }
private:
    float vx, vy;
};
