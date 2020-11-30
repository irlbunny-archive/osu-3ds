#ifndef __HIT_OBJECT_H__
#define __HIT_OBJECT_H__

namespace osu {
    class HitObject {
    public:
        virtual void Draw(u64 lTime);
    };
}

#endif // __HIT_OBJECT_H__