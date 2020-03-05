#ifndef __GAMETEXTURE_H__
#define __GAMETEXTURE_H__

/** Standard Includes **/
#include <string>

/** Hardware Specific Includes **/
#include <citro2d.h>

/** Local Includes **/
#include "../utils/common.h"

namespace graphics
{
    class GameTexture
    {
    private:
        inline static void Set(u32* buffer, u32 hex, u32 x, u32 y, u32 w, u32 h, u32 offset)
        {
            buffer[(Common::MortonDec(x, y, 1) + ((y & ~7) * w)) + offset] = __builtin_bswap32(hex);
        }
    public:
        static C2D_Sprite* Load(std::string path);
    };
}

#endif // __GAMETEXTURE_H__