#include "Paddle.h"
#include "Framework.h"

Paddle::Paddle(int x0, int y0)
    : Object("datas/paddle.png")
{
    this->SetX((double)x0/2.0);
    double height = this->GetHeight();
    this->SetY(y0 - height);
}

void Paddle::OnKBInput(sf::Key::Code KeyCode)
{
    float ElapsedTime = GetApp()->GetFrameTime();
    int resx, resy;
    GetResolution(&resx, &resy);

    // move
    if (KeyCode == sf::Key::Left)
    {
        this->Move(-150 * ElapsedTime, 0);
    }
    if (KeyCode == sf::Key::Right)
    {
        this->Move( 150 * ElapsedTime, 0);
    }

    // restrict motion to screen
    if(this->GetX() + this->GetWidth() > (double)resx)
    {
        this->SetX((double)resx - this->GetWidth());
    }
    if(this->GetX() < 0.0)
    {
        this->SetX(0.0);
    }
}

void Paddle::Update()
{
    DispatchKBInput(sf::Key::Left);
    DispatchKBInput(sf::Key::Right);
}

Paddle::~Paddle()
{
    //dtor
}
