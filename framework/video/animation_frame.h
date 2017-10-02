
#pragma once

class AnimationFrame
{
	public:
		int framenumber;
		int tickduration;

		AnimationFrame(int FrameNumber, int TickDuration) { framenumber = FrameNumber; tickduration = TickDuration; };
};
