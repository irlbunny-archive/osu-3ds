#ifndef _GAMEBASE_H
#define _GAMEBASE_H

#include "common.h"

#include "MainMenu.h"

class GameBase
{
private:
    C3D_RenderTarget* top;
    C3D_RenderTarget* bottom;

    MainMenu* mainMenu;

    void DrawTop();
    void DrawBottom();
public:
    GameBase();
    ~GameBase();

    void Run();

    void Update();
    void Draw();
};

#endif // _GAMEBASE_H