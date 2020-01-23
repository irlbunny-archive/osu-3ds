#include <map>

#include "GameTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "../utils/stb_image.h"
#include "../utils/stb_image_resize.h"

#include "../utils/common.h"

static std::map<std::string, C2D_Image> cache;

namespace graphics
{
    u32 GameTexture::MortonEnc(u32 x, u32 y)
    {
        u32 i = (x & 7) | ((y & 7) << 8); // ---- -210
        i = (i ^ (i << 2)) & 0x1313; // ---2 --10
        i = (i ^ (i << 1)) & 0x1515; // ---2 -1-0
        i = (i | (i >> 7)) & 0x3F;

        return i;
    }
    
    u32 GameTexture::Morton(u32 x, u32 y, u32 bytesPerPixel)
    {
        return (MortonEnc(x, y) + ((x & ~7) * 8)) * bytesPerPixel;
    }
    
    void GameTexture::SetPixel(u32* buffer, u32 hex, u32 x, u32 y, u32 w, u32 h, u32 offset)
    {
        hex = __builtin_bswap32(hex); // FIX: Should not be here, this is a hack.

        buffer[(Morton(x, y, 1) + ((y & ~7) * w)) + offset] = hex;
    }
    
    C2D_Sprite* GameTexture::Load(std::string path)
    {
        if (cache.find(path) == cache.end())
        {
            int w, h, n;
            unsigned char *data = stbi_load(path.c_str(), &w, &h, &n, 4);

            int resizedW = w, resizedH = h;

            resizedLoop:
            if (resizedW > 1023 || resizedH > 1023) // PICA-200 only supports textures up to 1023x1023.
            {
                resizedW = (int)(resizedW / 1.5);
                resizedH = (int)(resizedH / 1.5);

                goto resizedLoop;
            }
            else
            {
                stbir_resize_uint8(reinterpret_cast<u8*>(data), w, h, 0,
                    reinterpret_cast<u8*>(data), resizedW, resizedH, 0, 4);
            }

            w = resizedW, h = resizedH;

            u32 wPow2 = Common::Pow2(w), hPow2 = Common::Pow2(h);

            C3D_Tex* tex = new C3D_Tex;
            Tex3DS_SubTexture* subtex = new Tex3DS_SubTexture;

            C3D_TexInit(tex, static_cast<u16>(wPow2), static_cast<u16>(hPow2), GPU_RGBA8);
            C3D_TexSetFilter(tex, GPU_NEAREST, GPU_NEAREST);

            tex->border = 0xFFFFFFFF;

            C3D_TexSetWrap(tex, GPU_CLAMP_TO_BORDER, GPU_CLAMP_TO_BORDER);

            subtex->width = (u16)w;
            subtex->height = (u16)h;
            subtex->left = 0.0f;
            subtex->top = 1.0f;
            subtex->right = (w / static_cast<float>(wPow2));
            subtex->bottom = 1.0 - (h / static_cast<float>(hPow2));

            memset(tex->data, 0, tex->size);
            for (int x = 0; x < w; x++) 
            {
                for (int y = 0; y < h; y++) 
                    SetPixel(reinterpret_cast<u32*>(tex->data), (reinterpret_cast<u32*>(data))[y * w + x], x, y, wPow2, hPow2, 0);
            }

            C3D_TexFlush(tex);

            stbi_image_free(data);

            cache.insert({ path, C2D_Image{tex, subtex} });
        }

        C2D_Sprite* texture = new C2D_Sprite;
        C2D_SpriteFromImage(texture, cache[path]);
        
        return texture;
    }
}