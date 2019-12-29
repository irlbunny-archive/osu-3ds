#include "GameSprite.h"

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

void GameSprite::Draw(u32 x, u32 y)
{
    texture->params.pos.x = x;
    texture->params.pos.y = y;

    C2D_SpriteSetCenter(texture, 0.5f, 0.5f);

    C2D_DrawSprite(texture);
}