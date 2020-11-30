#ifndef __HITCIRCLE_H__
#define __HITCIRCLE_H__

#include "graphics/GameSprite.h"
#include "graphics/GameTexture.h"

class HitCircle {
    public:
        graphics::GameSprite* circle;
        graphics::GameSprite* overlay;
        graphics::GameSprite* approach;

        HitCircle(int X, int Y, long Timing);

        void DrawCircle(int X, int Y);
        void DrawApproach(int X, int Y, float Size);
        void DrawCircleAndApproach(long CurrentTiming);
    private:
        void   Reset();
        double DifficultyRange(double Difficulty, double Min, double Mid, double Max);
        
        float  Size         = 0.5f;
        float  ApproachSize = 1.0f;
        bool   Draw         = true;
        double HitRange     = 300;
        int    MSTick       = 0;
        long   StartTime    = 0;
        long   Timing       = 0;
        double ApproachRate = 11.0;
        int X = 0, Y = 0;
};

#endif // __HITCIRCLE_H__