#ifndef GAMECORE_H
#define GAMECORE_H

#include <list>
#include "Framework.h"
#include "Object.h"
using namespace std;

enum GameState
{
    run, losermsg
};

class GameCore
{
    public:
        // CTOR
        GameCore(int resx, int resy);
        virtual ~GameCore();
        // MISC
        void Update();
        void Draw();
        void DistributeKBInput(sf::Key::Code KeyCode);
    protected:
        void Push(Object *obj);
        void SpawnBlocks();
        bool CheckForDeath();
        void InitBall();
        void LoserMessage();
        bool CollisionCheck(Object *obj0, Object *obj1);
    private:
        list<Object*> m_obj_list;             // list of game objects
        int m_resx, m_resy;
        GameState m_state;
};

#endif // GAMECORE_H
