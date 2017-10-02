
#pragma once

#include "../events/event.h"
#include "../primitives/point.h"

#define PFX_MAX_MOUSE_BUTTONS	10

class Mouse
{

	private:
		Display* activedisplay;
		bool buttonsdown[PFX_MAX_MOUSE_BUTTONS];

	public:
		Point<int> position;
		int wheelvertical;
		int wheelhorizontal;

		Mouse();

		void OnEvent(Event* What);

		int GetButtonCount();
		bool IsButtonDown(int ButtonNumber);

		Display* GetActiveDisplay();

		void Warp(Point<int> Position);

};
