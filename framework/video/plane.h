
#pragma once

#include "display.h"
#include "../events/event.h"

class Plane
{

	protected:
		Display* display;
		

	public:
		unsigned char alpha;
		Point<int> scrolloffset;

		Plane(Display* Owner) { display = Owner; display->planes.Add( this ); alpha = 255; scrolloffset.x = 0; scrolloffset.y = 0; };
		virtual ~Plane() {};

		virtual void EventOccured(Event* What) = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

};
