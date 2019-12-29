#ifndef _MAINMENU_H
#define _MAINMENU_H

#include "common.h"

#include "GameSprite.h"
#include "GameText.h"
#include "GameTexture.h"

class MainMenu
{
private:
    GameSprite* menuBackground;
    GameSprite* menuOsu;

    float menuOsuScale;

    GameSprite* buttonPlay;
    GameSprite* buttonOptions;
    GameSprite* buttonExit;

    GameText* copyright;
public:
    MainMenu();

    void Update();

    void DrawTop();
    void DrawBottom();
};

#endif // _MAINMENU_H