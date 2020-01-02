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

        if (color != C2D_Color32(0x00, 0x00, 0x00, 0x00))
        {
            C2D_ImageTint tint;

            for (u8 index = 0; index < 4; index++)
            {
                tint.corners[index].color = color;
                tint.corners[index].blend = .5;
            }

            C2D_DrawSpriteTinted(texture, &tint);
        }
        else C2D_DrawSprite(texture);
    }
}