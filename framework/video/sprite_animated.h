
#pragma once

#include "sprite.h"
#include "animation.h"

class AnimatedSprite : public Sprite
{

	public:
		Animation* animation;

		AnimatedSprite(Atlas* FrameSet, Animation* AnimationData);

		void Update() override;

};
