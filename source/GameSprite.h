#ifndef _GAMESPRITE_H
#define _GAMESPRITE_H

#include "common.h"

class GameSprite
{
private:
    C2D_Sprite* texture;
public:
    GameSprite(C2D_Sprite* texture);

    void Scale(float value);
    void Scale(float x, float y);
    
    void Draw(u32 x, u32 y);
};

#endif // _GAMESPRITE_H