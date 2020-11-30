#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include <citro2d.h>

namespace graphics
{
    class GameSprite
    {
    private:
        C2D_Sprite* texture;
    public:
        float fTint = 1.0;
    public:
        GameSprite(C2D_Sprite* texture);
        
        void Scale(float value);
        void Scale(float x, float y);

        void Draw(u32 x, u32 y, u32 color = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
    };
}

#endif // __GAMESPRITE_H__