#include <SFML/Graphics.hpp>
#include "Framework.h"
#include "Object.h"
#include "Ball.h"
#include "Block.h"
#include "Paddle.h"
#include "Button.h"
#include "Menu.h"
#include "GameCore.h"
#include <iostream>
#include <list>
#include <stdio.h>
using namespace std;

sf::RenderWindow App;
int resx = 800, resy = 600;
list<Object*> obj_list;                             // Global object list
list<Button*> button_list;                          // list of buttons for the menu
Menu *mainmenu;                                     // The main menu
GameCore *gamecore;                                 // The actual game
sf::Font font;                                      // Font for text
ProgramState progstate = loadmenu;                  // execution state of program


bool CollisionCheck(Object *obj0, Object *obj1);

// Set Current Program State
void SetProgramState(ProgramState ps)
{
    progstate = ps;
}

// Init the App
void Init(void)
{
    // Create App
    App.Create(sf::VideoMode(resx, resy, 32), "SFML Breakout");
    // Load Font
    if (!font.LoadFromFile("datas/cheeseburger.ttf"))
    {
        cout << "could not load text font" << endl;
    }
}

sf::RenderWindow *GetApp()
{
    return &App;
}

void GetResolution(int *resx_, int *resy_)
{
    // Rem: Could also be done with App.GetWidth(), App.GetHeight()

    *resx_ = resx;
    *resy_ = resy;
}

// Draw some text on screen
void DrawText(string text, int x, int y, int size)
{
    sf::String Text;
    Text.SetFont(font);
    Text.SetSize(double(size));
    Text.Move(double(x), double(y));
    Text.SetColor(sf::Color(50, 50, 250));
    Text.SetText(text);
    App.Draw(Text);
}

// Distribute input to all objects
void DistributeKBInput(list<Object*> *lst, sf::Key::Code KeyCode)
{
    list<Object*>::iterator it;

    for (it=lst->begin() ; it != lst->end(); it++ )
    {
        (*it)->OnKBInput(KeyCode);
    }
}

// Run function for in-game
void InGame_Driver(void)
{
    // Handle Escape
    sf::Event Event;
    while (App.GetEvent(Event))
    {
        // Escaping the App
        if ((Event.Type == sf::Event::Closed) ||
                ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)))
        {
            progstate = inmenu;
            break;
        }
    }

    // Clear the window
    App.Clear();

    // Update and Collision Detection
    gamecore->Update();

    // Draw Objects
    gamecore->Draw();

    // Display things on screen
    App.Display();
}

// Run function for loading the level
void LoadGamecore_Driver()
{
    static bool loadflag = false;

    if(loadflag == false)
    {
        gamecore = new GameCore(resx, resy);
        cout << "Game loaded" << endl;
        loadflag = true;
    }

    progstate = ingame;
}

// Run function for closing the program
void Close_Driver()
{
    App.Close();
}

// Run function for loading the level
void InMenu_Driver()
{
    // Handle Escape
    sf::Event Event;
    while (App.GetEvent(Event))
    {
        // Escaping the App
        if ((Event.Type == sf::Event::Closed) ||
                ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)))
        {
            progstate = closing;
            break;
        }
    }

    // Clear the window
    App.Clear();

    // Update and Collision Detection
    mainmenu->Update();

    // Draw Objects
    mainmenu->Draw();

    // Display things on screen
    App.Display();
}

// Run function for loading the level
void LoadMenu_Driver()
{
    static bool loadflag = false;

    if(loadflag == false)
    {
        mainmenu = new Menu();
        cout << "Menu loaded" << endl;
        loadflag = true;
    }

    progstate = inmenu;
}

// Core Loop of program
void Run(void)
{

    while (App.IsOpened())
    {
        if(progstate == loadmenu)
        {
            LoadMenu_Driver();
        }
        if(progstate == inmenu)
        {
            InMenu_Driver();
        }
        if(progstate == loadgamecore)
        {
            LoadGamecore_Driver();
        }
        if(progstate == ingame)
        {
            InGame_Driver();
        }
        if(progstate == closing)
        {
            Close_Driver();
        }
    }
}

