#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "graphics/GameSprite.h"
#include "graphics/GameText.h"
#include "graphics/GameTexture.h"

namespace states
{
    class MainMenu
    {
    private:
        graphics::GameSprite* background;
        graphics::GameSprite* osu;

        float osuScale;

        graphics::GameSprite* buttonPlay;
        graphics::GameSprite* buttonOptions;

        graphics::GameText* copyright;
    public:
        MainMenu();

        void Update();
        
        void DrawTop();
        void DrawBottom();
    };
}

#endif // __MAINMENU_H__