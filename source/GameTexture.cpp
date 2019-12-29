#include "GameTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_resize.h"

// FIX: These should be in the header, but it causes an issue when linking.
static int resizedW;
static int resizedH;

u32 GameTexture::Pow2(u32 v) // TODO: Move this to a different file?
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;

    return v >= 64 ? v : 64;
}

u32 GameTexture::MortonEnc(u32 x, u32 y) // FIX(?): Should be MortonDec?
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

void GameTexture::Resize(void* buffer, int w, int h)
{
    if (resizedW >= 1024 || resizedW >= 1024) // The 3DS does not support textures above 1023x1023, I think.
    {
        resizedW = (int)(resizedW / 1.5f);
        resizedH = (int)(resizedH / 1.5f);

        Resize(buffer, w, h);
    }
    else
    {
        stbir_resize_uint8((u8*)buffer, w, h, 0,
            (u8*)buffer, resizedW, resizedH, 0, 4);
    }
}

C2D_Sprite* GameTexture::Load(std::string path)
{
    int w, h, n;
    unsigned char *data = stbi_load(path.c_str(), &w, &h, &n, 4);

    resizedW = w;
    resizedH = h;

    Resize(data, w, h);

    w = resizedW;
    h = resizedH;

    u32 wPow2 = Pow2(w);
    u32 hPow2 = Pow2(h);

    C3D_Tex* tex = new C3D_Tex;
    Tex3DS_SubTexture* subtex = new Tex3DS_SubTexture;

    C3D_TexInit(tex, (u16)wPow2, (u16)hPow2, GPU_RGBA8);
    C3D_TexSetFilter(tex, GPU_NEAREST, GPU_NEAREST);

    tex->border = 0xFFFFFFFF;
    
    C3D_TexSetWrap(tex, GPU_CLAMP_TO_BORDER, GPU_CLAMP_TO_BORDER);

    subtex->width = (u16)w;
    subtex->height = (u16)h;
    subtex->left = 0.0f;
    subtex->top = 1.0f;
    subtex->right = (w / (float)wPow2);
    subtex->bottom = 1.0 - (h / (float)hPow2);

    memset(tex->data, 0, tex->size);
    for (int x = 0; x < w; x++) 
    {
        for (int y = 0; y < h; y++) 
        {
            SetPixel((u32*)tex->data, ((u32*)data)[y * w + x], x, y, wPow2, hPow2, 0);
        }
    }

    stbi_image_free(data);

    C2D_Sprite* texture = new C2D_Sprite;

    C3D_TexFlush(tex);
    C2D_SpriteFromImage(texture, C2D_Image{tex, subtex});

    return texture;
}