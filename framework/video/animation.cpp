
#include "animation.h"

Animation::Animation()
{
	loopanimation = true;
	Start();
}

void Animation::Start()
{
	currentframe = 0;
	currentframeticks = 0;
}

void Animation::Animate()
{
	// Make sure the animation hasn't gone wrong
	if( currentframe >= frames.Count() )
	{
		currentframe = ( loopanimation ? 0 : frames.Count() - 1 );
		currentframeticks = 0;
	}

	AnimationFrame* f = frames.At( currentframe );

	currentframeticks++;
	if( currentframeticks >= f->tickduration )
	{
		currentframe++;
		currentframeticks = 0;
		if( currentframe >= frames.Count() )
		{
			currentframe = ( loopanimation ? 0 : -1 );
		}
	}

}

int Animation::GetFrameNumber()
{
	if( currentframe < 0 )
	{
		return -1;
	}
	return frames.At( currentframe )->framenumber;
}
