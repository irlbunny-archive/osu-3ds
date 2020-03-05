#ifndef __COMMON_H__
#define __COMMON_H__

class Common
{
public:
    inline static u32 Pow2(u32 v)
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

    inline static u32 MortonEnc(u32 x, u32 y)
    {
        u32 i = (x & 7) | ((y & 7) << 8); // ---- -210
        i = (i ^ (i << 2)) & 0x1313; // ---2 --10
        i = (i ^ (i << 1)) & 0x1515; // ---2 -1-0
        i = (i | (i >> 7)) & 0x3F;

        return i;
    }

    inline static u32 MortonDec(u32 x, u32 y, u32 bytesPerPixel)
    {
        return (MortonEnc(x, y) + ((x & ~7) * 8)) * bytesPerPixel;
    }
};

#endif // __COMMON_H__