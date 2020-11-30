#include "HitCircle.h"

HitCircle::HitCircle(int X, int Y, long Timing) {
	this->circle = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/hitcircle.png"));
	this->overlay = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/hitcircleoverlay.png"));
	this->approach = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/approachcircle.png"));

	this->X = X;
	this->Y = Y;
	this->Timing = Timing;
}

void HitCircle::DrawCircle(int X, int Y) {
	circle->Scale(Size);
	circle->Draw(X, Y);

	overlay->Scale(Size);
	overlay->Draw(X, Y);
}

void HitCircle::DrawApproach(int X, int Y, float Size) {
	approach->Scale(Size);
	approach->Draw(X, Y);
}

void HitCircle::DrawCircleAndApproach(long CurrentTiming) {
	double PreApproachTime    = DifficultyRange(ApproachRate, 1800, 1200, 450);
	double ActualApproachRate = PreApproachTime > 1200 ? (1800 - PreApproachTime) / 120 : (1200 - PreApproachTime) / 150 + 5;
	double ApproachTime       = DifficultyRange(ActualApproachRate, 1800, 1200, 450);

	if (CurrentTiming + (ApproachTime) + 100 > Timing && CurrentTiming - (ApproachTime) < Timing) {
		if (Draw) {
			if (CurrentTiming + (ApproachTime) + 100 > Timing && CurrentTiming - (ApproachTime / 10) < Timing) {
				if (StartTime == 0) {
					StartTime = CurrentTiming;
					MSTick    = CurrentTiming - StartTime;
				}

				DrawCircle(X, Y);

				long  Difference          = (CurrentTiming - Timing);
				float Doub                = 2 * ApproachTime;
				float CurrentApproachSize = (-1 * (Difference / Doub)) + 0.5;

				if (Difference > (-1 * ApproachTime * HitRange) && Difference < 0) {
					MSTick = CurrentTiming - StartTime;
					DrawApproach(X, Y, CurrentApproachSize);
				} else if (CurrentTiming + (ApproachTime) > Timing && Difference < 0) {
					DrawApproach(X, Y, 1.0f);
				}
			}
		}
	} else {
		Reset();
	}
}

void HitCircle::Reset() {
	Draw         = true;
	ApproachSize = 1.0f;
	MSTick       = 0;
	StartTime    = 0;
}

double HitCircle::DifficultyRange(double Difficulty, double Min, double Mid, double Max) {
	if (Difficulty > 5)
		return Mid + (Max - Mid) * (Difficulty - 5) / 5;
	if (Difficulty < 5)
		return Mid - (Mid - Min) * (5 - Difficulty) / 5;
	return Mid;
}