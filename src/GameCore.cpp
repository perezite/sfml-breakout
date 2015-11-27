#include "GameCore.h"
#include "Object.h"
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Framework.h"


GameCore::GameCore(int resx, int resy)
{
    m_resx = resx;
    m_resy = resy;
    m_state = run;

    // insert objects
    Object *object = new Paddle(resx, resy);
    Object *object2 = new Ball();
    object2->SetX(float(resx)/2.0);
    object2->SetY(float(resy)/2.0);
    Push(object);
    Push(object2);
    SpawnBlocks();
}

GameCore::~GameCore()
{
    //dtor
}

void GameCore::Draw()
{
    if(m_state == run)
    {
        list<Object*>::iterator it;

        for (it=m_obj_list.begin() ; it != m_obj_list.end(); it++ )
        {
            GetApp()->Draw(*((*it)->GetSprite()));
        }
    }

    if(m_state == losermsg)
    {
        // Draw loser message
        DrawText("LOSER! You lost the ball\nPress Enter to continue..", double(m_resx)/4.0, double(m_resy)/2.0, 30);
    }
}

void GameCore::Update()
{
    if(m_state == running)
    {
        list<Object*>::iterator it1;
        list<Object*>::iterator it2;

        // Update all objects
        for (it1=m_obj_list.begin() ; it1 != m_obj_list.end(); it1++ )
        {
            (*it1)->Update();
        }

        // Collision Check
        for (it1=m_obj_list.begin() ; it1 != m_obj_list.end(); it1++ )
        {
            for (it2=it1, it2++ ; it2 != m_obj_list.end(); it2++ )
            {
                CollisionCheck(*it1, *it2);
            }
        }

        // Delete objects, which have state "deletion"
        for (it1=m_obj_list.begin() ; it1 != m_obj_list.end(); it1++ )
        {
            int state = (*it1)->GetState();
            if(state == deletion)
            {
                it1 = m_obj_list.erase(it1);      // it1 points to element after erased one
                it1--;                      // so, set it one element back, because
                // it is set to next elem. in next for iteration
                cout << m_obj_list.size() << endl;
            }
        }

        // Check if player has lost the ball
        if(CheckForDeath())
        {
            m_state = losermsg;
        }
    }

    if(m_state == losermsg)
    {
        LoserMessage();
    }

}

void GameCore::DistributeKBInput(sf::Key::Code KeyCode)
{
    list<Object*>::iterator it;

    for (it=m_obj_list.begin() ; it != m_obj_list.end(); it++ )
    {
        (*it)->OnKBInput(KeyCode);
    }
}

// Push a new Object into the list
void GameCore::Push(Object *obj)
{
    m_obj_list.push_back(obj);
}

// spawn some random blocks on field
void GameCore::SpawnBlocks(void)
{
    for(int i = 0; i < 10; i++)
    {
        int x = 50 * (rand()%10);
        int y = 50 * (rand()%10);
        Push(new Block(x, y, yellow));
    }
    for(int i = 0; i < 10; i++)
    {
        int x = 50 * (rand()%10);
        int y = 50 * (rand()%10);
        Push(new Block(x, y, blue));
    }
    for(int i = 0; i < 10; i++)
    {
        int x = 50 * (rand()%10);
        int y = 50 * (rand()%10);
        Push(new Block(x, y, green));
    }
}

bool GameCore::CheckForDeath(void)
{
    list<Object*>::iterator it;

    // Find all balls in game
    for (it=m_obj_list.begin() ; it != m_obj_list.end(); it++ )
    {
        if((*it)->GetType() == ball)
        {
            double y = (*it)->GetY();
            if(y > m_resy)
            {
                return true;
            }
        }
    }

    return false;
}

void GameCore::InitBall(void)
{
    list<Object*>::iterator it;

    // delete old balls
    for (it=m_obj_list.begin() ; it != m_obj_list.end(); it++ )
    {
        if((*it)->GetType() == ball)
        {
            it = m_obj_list.erase(it);      // it1 points to element after erased one
            it--;                      // so, set it one element back, because
            // it is set to next elem. in next for iteration
        }
    }

    // insert new ball
    Object *object = new Ball();
    object->SetX(float(m_resx)/2.0);
    object->SetY(float(m_resy)/2.0);
    Push(object);
}

void GameCore::LoserMessage()
{
    // Handle Escape
    sf::Event Event;
    while (GetApp()->GetEvent(Event))
    {
        // Escaping the App
        if ((Event.Type == sf::Event::Closed) ||
                ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)))
        {
            SetProgramState(closing);
            break;
        }
    }

    // Keyboard Input
    if (GetApp()->GetInput().IsKeyDown(sf::Key::Return))
    {
        InitBall();
        m_state = run;
    }
}

bool GameCore::CollisionCheck(Object *obj0, Object *obj1)
{
    float obj0_x0 = obj0->GetX();
    float obj0_y0 = obj0->GetY();
    float obj0_x1 = obj0_x0 + obj0->GetWidth();
    float obj0_y1 = obj0_y0 + obj0->GetHeight();
    float obj1_x0 = obj1->GetX();
    float obj1_y0 = obj1->GetY();
    float obj1_x1 = obj1_x0 + obj1->GetWidth();
    float obj1_y1 = obj1_y0 + obj1->GetHeight();

    if( ( (obj0_x0 >= obj1_x0 and obj0_x0 <= obj1_x1) or (obj0_x1 >= obj1_x0 and obj0_x1 <= obj1_x1) or (obj1_x0 >= obj0_x0 and obj1_x0 <= obj0_x1) )  and
            ( (obj0_y0 >= obj1_y0 and obj0_y0 <= obj1_y1) or (obj0_y1 >= obj1_y0 and obj0_y1 <= obj1_y1) or (obj1_y0 >= obj0_y0 and obj1_y0 <= obj0_y1))     )
    {
        obj0->Collision(obj1);
        obj1->Collision(obj0);
    }

    return false;
}
