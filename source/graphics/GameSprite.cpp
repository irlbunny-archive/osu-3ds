#include "GameSprite.h"

namespace graphics
{
    GameSprite::GameSprite(C2D_Sprite* texture)
    {
        this->texture = texture;
    }
    
    void GameSprite::Scale(float value)
    {
        C2D_SpriteSetScale(texture, value, value);
    }
    
    void GameSprite::Scale(float x, float y)
    {
        C2D_SpriteSetScale(texture, x, y);
    }
    
    void GameSprite::Draw(u32 x, u32 y, u32 color)
    {
        texture->params.pos.x = x;
        texture->params.pos.y = y;
    
        C2D_SpriteSetCenter(texture, .5, .5);

        C2D_ImageTint tint;
        C2D_PlainImageTint(&tint, color, 1.0f - ((color >> 24 & 0xFF) / 255.0f));
        C2D_DrawSpriteTinted(texture, &tint);
    }
}