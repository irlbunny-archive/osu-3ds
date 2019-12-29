#include "GameText.h"

static C2D_TextBuf textBuf = C2D_TextBufNew(512);

GameText::GameText(std::string value)
{
    this->text = new C2D_Text;

    Set(value);
}

void GameText::Set(std::string value)
{
    C2D_TextParse(text, textBuf, value.c_str());
    C2D_TextOptimize(text);
}

void GameText::Draw(float x, float y, float z, float scaleX, float scaleY)
{
    C2D_DrawText(text, C2D_WithColor, x, y, z, scaleX, scaleY, color);
}