#ifndef __GAMETEXT_H__
#define __GAMETEXT_H__

#include <string>
#include <citro2d.h>

namespace graphics
{
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
}

#endif // __GAMETEXT_H__