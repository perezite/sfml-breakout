#ifndef __FRAMEWORK_H
#define __FRAMEWORK_H
#include <SFML/Graphics.hpp>
#include "Object.h"

// execution state of the program
enum ProgramState
{
    loadmenu,
    inmenu,
    ingame,
    loadgamecore, // program is loading the level
    closing   // program is about to close
};


void Init(void);
void Run(void);
bool CollisionCheck(Object *obj0, Object *obj1);
sf::RenderWindow *GetApp();
void GetResolution(int *resx_, int *resy_);
void SetProgramState(ProgramState ps);
void DrawText(string text, int x, int y, int size);

#endif
