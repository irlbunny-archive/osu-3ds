#ifndef __GAMEBASE_H__
#define __GAMEBASE_H__

#include <citro2d.h>

#include "states/MainMenu.h"

class GameBase
{
private:
    C3D_RenderTarget* top;
    C3D_RenderTarget* bottom;

    states::MainMenu* mainMenu;

    void DrawTop();
    void DrawBottom();
public:
    GameBase();
    ~GameBase();

    void Run();

    void Update();
    void Draw();
};

#endif // __GAMEBASE_H__