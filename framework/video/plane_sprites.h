
#pragma once

#include "plane.h"
#include "sprite.h"
#include "sprite_animated.h"
#include "sprite_shape.h"
#include "sprite_text.h"
#include "../core/indexsort.h"

class SpritePlaneDrawOrder
{
	public:
		enum DrawOrder
		{
			LIST,
			LISTREVERSED,
			XPOSITION,
			XPOSITIONREVERSED,
			YPOSITION,
			YPOSITIONREVERSED
		};
};

class SpritePlane : public Plane
{
	public:
		List<Sprite*> sprites;
		SpritePlaneDrawOrder::DrawOrder draworder;

		SpritePlane(Display* Owner);

		void EventOccured(Event* What) override;
		void Update() override;
		void Render() override;
};
