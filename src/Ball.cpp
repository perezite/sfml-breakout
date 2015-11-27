#include "Ball.h"
#include <math.h>
#include "Framework.h"

Ball::Ball()
    :   Object("datas/ball.png")
{
    vx = -20;
    vy = 200.0;
    SetX(400);
    SetY(300);
}

void Ball::Update()
{
//    cout << "Ball update" << endl;

    float ElapsedTime = GetApp()->GetFrameTime();
    int resx, resy;
    GetResolution(&resx, &resy);

    // Move Ball
    Move(vx*ElapsedTime, vy*ElapsedTime);

    // Check for collision with wall
    if(GetX() <= 0)                         // impact onto left wall
    {
        SetX(0);
        vx = -vx;
    }
    if( (GetX() + GetWidth()) >= resx)      // impact onto right wall
    {
        SetX(resx - GetWidth());
        vx = -vx;
    }
    if(GetY() <= 0)      // impact onto top wall
    {
        SetY(0);
        vy = -vy;
    }
}

void Ball::Collision(Object *obj)
{
    float ElapsedTime = GetApp()->GetFrameTime();
    float rev_vx = -vx;                     // reversed velocity
    float rev_vy = -vy;

    // recover position of ball from last frame
    // (such that ball does not get stuck)
    Move(rev_vx*ElapsedTime, rev_vy*ElapsedTime);

    // reflect velocity, according to impact direction of ball
    float thisx0 = this->GetX();
    float thisx1 = thisx0 + this->GetWidth();
    float thisy0 = this->GetY();
    float thisy1 = thisy0 + this->GetHeight();
    float otherx0 = obj->GetX();
    float otherx1 = otherx0 + obj->GetWidth();
    float othery0 = obj->GetY();
    float othery1 = othery0 + obj->GetHeight();
    // ball impact from above
    if( thisy1 < othery0)
    {
        vy = -vy;
    }
    // ball impact from below
    if( thisy0 > othery1)
    {
        vy = -vy;
    }
    // ball impact from left
    if( thisx1 < otherx0)
    {
        vx = -vx;
    }
    // ball impact from right
    if( thisx0 > otherx1)
    {
        vx = -vx;
    }

    // Do extra correction according to x-coord of ball rel. to paddle
    // such that impact pos. on paddle controls reflection behaviour
    if(obj->GetType() == paddle)
    {
        double thismid = this->GetX() + (this->GetWidth() * 0.5);
        double objmid = obj->GetX() + (obj->GetWidth() * 0.5);
        double objhalf = obj->GetWidth() * 0.5;
        double ratio = (thismid - objmid)/objhalf;
        double len1 = sqrt(vx*vx + vy*vy);
        vx /= len1;
        vy /= len1;
        vx += ratio * 0.5;
        double len2 = sqrt(vx*vx + vy*vy);
        vx /= len2;
        vy /= len2;
        vx *= len1;
        vy *= len1;
    }
}
