
#include "sprite_animated.h"

AnimatedSprite::AnimatedSprite(Atlas* FrameSet, Animation* AnimationData) : Sprite(FrameSet, 0)
{
	animation = AnimationData;
	animation->Start();
	atlasframe = animation->GetFrameNumber();
}

void AnimatedSprite::Update()
{
	animation->Animate();
	atlasframe = animation->GetFrameNumber();
}
