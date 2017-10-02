

#pragma once

#include "animation_frame.h"
#include "../core/list.h"

class Animation
{

	private:
		int currentframeticks;

	public:
		bool loopanimation;
		int currentframe;
		List<AnimationFrame*> frames;

		Animation();

		void Start();
		void Animate();

		int GetFrameNumber();

};
