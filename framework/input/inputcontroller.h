
#pragma once

#include "../libraryincludes.h"
#include "../core/list.h"
#include "joypad.h"
#include "keyboard.h"
#include "mouse.h"

class InputController
{

	private:
#ifdef ALLEGRO
		ALLEGRO_EVENT_QUEUE* eventqueue;
#endif // ALLEGRO

	public:
		Keyboard keyboard;
		Mouse mouse;
		List<Joystick*> joysticks;

		void Initalise();
		void Shutdown();
		void RefreshJoysticks();

		void Update();

};
