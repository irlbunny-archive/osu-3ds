/** Standard Includes **/
#include <map>

/** Local Includes **/
#include "GameTexture.h"

// Define our STB image and resize implementation.
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "../utils/stb_image.h"
#include "../utils/stb_image_resize.h"

static std::map<std::string, C2D_Image> cache;

namespace graphics
{
    C2D_Sprite* GameTexture::Load(std::string path)
    {
        if (cache.find(path) == cache.end())
        {
            int w, h, n;
            u8* image = stbi_load(path.c_str(), &w, &h, &n, 4);
            
            int _w = w, _h = h;

            while (1)
            {
                if (_w > 1023 || _h > 1023) // PICA-200 only supports textures up to 1023x1023.
                {
                    _w = (int)(_w / 1.5);
                    _h = (int)(_h / 1.5);
                }
                else
                {
                    u8* resized = reinterpret_cast<u8*>(malloc(_w * _h * 4));

                    stbir_resize_uint8(reinterpret_cast<u8*>(image), w, h, 0,
                        reinterpret_cast<u8*>(resized), _w, _h, 0, 4);

                    stbi_image_free(image);

                    image = resized;

                    break;
                }
            }

            w = _w, h = _h;

            u32 wPow2 = Common::Pow2(w), hPow2 = Common::Pow2(h);

            C3D_Tex* tex = new C3D_Tex;
            Tex3DS_SubTexture* subtex = new Tex3DS_SubTexture;

            C3D_TexInit(tex, static_cast<u16>(wPow2), static_cast<u16>(hPow2), GPU_RGBA8);
            C3D_TexSetFilter(tex, GPU_NEAREST, GPU_NEAREST);

            tex->border = 0xFFFFFFFF;

            C3D_TexSetWrap(tex, GPU_CLAMP_TO_BORDER, GPU_CLAMP_TO_BORDER);

            subtex->width = static_cast<u16>(w);
            subtex->height = static_cast<u16>(h);
            subtex->left = 0.0f;
            subtex->top = 1.0f;
            subtex->right = (w / static_cast<float>(wPow2));
            subtex->bottom = 1.0 - (h / static_cast<float>(hPow2));

            memset(tex->data, 0, tex->size);
            for (int x = 0; x < w; x++) 
            {
                for (int y = 0; y < h; y++) 
                    Set(reinterpret_cast<u32*>(tex->data), (reinterpret_cast<u32*>(image))[y * w + x], x, y, wPow2, hPow2, 0);
            }

            C3D_TexFlush(tex);

            stbi_image_free(image);

            cache.insert({ path, C2D_Image{tex, subtex} });
        }

        C2D_Sprite* texture = new C2D_Sprite;
        C2D_SpriteFromImage(texture, cache[path]);
        
        return texture;
    }
}