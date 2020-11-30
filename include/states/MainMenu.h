#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "graphics/GameSprite.h"
#include "graphics/GameTexture.h"

#include "../HitCircle.h"

#include <vector>

namespace states
{
    class MainMenu
    {
    private:
        graphics::GameSprite* background;
        graphics::GameSprite* osu;
        
        float osuScale;

        graphics::GameSprite* osuFade;

        graphics::GameSprite* buttonPlay;
        graphics::GameSprite* buttonOptions;
    public:
        MainMenu();

        void Update();
        
        void DrawTop();
        void DrawBottom();
    };
}

#endif // __MAINMENU_H__