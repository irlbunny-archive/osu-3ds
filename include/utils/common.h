#ifndef __COMMON_H__
#define __COMMON_H__

class Common
{
public:
    static u32 Pow2(u32 v)
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
};

#endif // __COMMON_H__