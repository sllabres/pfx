
#pragma once

#include "atlas.h"

class Sprite
{

	protected:
		Bitmap* image;
		Atlas* atlas;
		int atlasframe;

	public:
		Point<int> position;
		Point<int> draworigin;
		Angle rotation;
		Size<float> scale;	// Use negative scales to "flip"

		Sprite();
		Sprite(Bitmap* Source);
		Sprite(Atlas* FrameSet, int Frame);

		Size<int> GetDimensions();

		virtual void Update();
		virtual void Render();
		virtual void Render(unsigned char Alpha);

};
