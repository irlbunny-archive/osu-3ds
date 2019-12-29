#ifndef _GAMETEXT_H
#define _GAMETEXT_H

#include "common.h"

class GameText
{
private:
    C2D_Text* text;
public:
    u32 color = C2D_Color32(0x00, 0x00, 0x00, 0xFF);

    GameText(std::string value = "");
    
    void Set(std::string value = "");

    void Draw(float x, float y, float z = .5f, float scaleX = .5f, float scaleY = .5f);
};

#endif // _GAMETEXT_H