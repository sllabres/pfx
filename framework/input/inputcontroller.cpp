
#include "inputcontroller.h"
#include "../pfx.h"

#ifdef ALLEGRO

void InputController::Initalise()
{
	// al_install_keyboard();
	// al_install_joystick();
	// al_install_mouse();

	eventqueue = al_create_event_queue();
	al_register_event_source( eventqueue, al_get_keyboard_event_source() );
	al_register_event_source( eventqueue, al_get_joystick_event_source() );
	al_register_event_source( eventqueue, al_get_mouse_event_source() );

	RefreshJoysticks();
}

void InputController::Shutdown()
{
	al_unregister_event_source( eventqueue, al_get_keyboard_event_source() );
	al_unregister_event_source( eventqueue, al_get_joystick_event_source() );
	al_unregister_event_source( eventqueue, al_get_mouse_event_source() );
	al_destroy_event_queue( eventqueue );

	// al_uninstall_mouse();
	// al_uninstall_joystick();
	// al_uninstall_keyboard();
}

void InputController::Update()
{
	ALLEGRO_EVENT ae;
	Event* fxe;
	bool forkb = false;
	bool forms = false;
	bool forjs = false;
	ALLEGRO_USTR* convert = al_ustr_new("");
	Point<int> mousepos;

	while( al_get_next_event( eventqueue, &ae ) )
	{
		fxe = nullptr;

		switch( ae.type )
		{
			case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
				al_reconfigure_joysticks();
				RefreshJoysticks();
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_INPUT_KEYBOARD_KEYDOWN;
				fxe->data.input.keyboard.keycode = ae.keyboard.keycode;
				fxe->data.input.keyboard.character = nullptr;
				fxe->data.input.keyboard.mappedkeyid = 0;
				fxe->data.input.keyboard.modifiers = 0;
				fxe->data.input.keyboard.modifiers |= ((ae.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT) == ALLEGRO_KEYMOD_SHIFT ? KEYMOD_SHIFT : 0);
				fxe->data.input.keyboard.modifiers |= ((ae.keyboard.modifiers & ALLEGRO_KEYMOD_ALT) == ALLEGRO_KEYMOD_ALT ? KEYMOD_ALT : 0);
				fxe->data.input.keyboard.modifiers |= ((ae.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL) == ALLEGRO_KEYMOD_CTRL ? KEYMOD_CTRL : 0);
				forkb = true;
				break;
			case ALLEGRO_EVENT_KEY_UP:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_INPUT_KEYBOARD_KEYUP;
				fxe->data.input.keyboard.keycode = ae.keyboard.keycode;
				fxe->data.input.keyboard.character = nullptr;
				fxe->data.input.keyboard.mappedkeyid = 0;
				fxe->data.input.keyboard.modifiers = 0;
				fxe->data.input.keyboard.modifiers |= ((ae.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT) == ALLEGRO_KEYMOD_SHIFT ? KEYMOD_SHIFT : 0);
				fxe->data.input.keyboard.modifiers |= ((ae.keyboard.modifiers & ALLEGRO_KEYMOD_ALT) == ALLEGRO_KEYMOD_ALT ? KEYMOD_ALT : 0);
				fxe->data.input.keyboard.modifiers |= ((ae.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL) == ALLEGRO_KEYMOD_CTRL ? KEYMOD_CTRL : 0);
				forkb = true;
				break;
			case ALLEGRO_EVENT_KEY_CHAR:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_INPUT_KEYBOARD_KEYPRESS;
				fxe->data.input.keyboard.keycode = ae.keyboard.keycode;				
				al_ustr_append_chr( convert, ae.keyboard.unichar );
				if( convert->slen == 1 && al_cstr(convert)[0] != 0 )
				{
					fxe->data.input.keyboard.character = new std::string( al_cstr(convert) );
				} else {
					fxe->data.input.keyboard.character = nullptr;
				}
				fxe->data.input.keyboard.mappedkeyid = 0;
				fxe->data.input.keyboard.modifiers = 0;
				fxe->data.input.keyboard.modifiers |= ((ae.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT) == ALLEGRO_KEYMOD_SHIFT ? KEYMOD_SHIFT : 0);
				fxe->data.input.keyboard.modifiers |= ((ae.keyboard.modifiers & ALLEGRO_KEYMOD_ALT) == ALLEGRO_KEYMOD_ALT ? KEYMOD_ALT : 0);
				fxe->data.input.keyboard.modifiers |= ((ae.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL) == ALLEGRO_KEYMOD_CTRL ? KEYMOD_CTRL : 0);
				forkb = true;
				break;

			case ALLEGRO_EVENT_MOUSE_AXES:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_INPUT_MOUSE_MOVE;
				fxe->data.input.mouse.x = ae.mouse.x;
				fxe->data.input.mouse.y = ae.mouse.y;
				fxe->data.input.mouse.deltax = ae.mouse.dx;
				fxe->data.input.mouse.deltay = ae.mouse.dy;
				fxe->data.input.mouse.wheelvertical = ae.mouse.z;
				fxe->data.input.mouse.wheelhorizontal = ae.mouse.w;
				fxe->data.input.mouse.button = ae.mouse.button;
				fxe->data.input.mouse.display = FX->video.FindDisplay( ae.mouse.display );
				mousepos = fxe->data.input.mouse.display->DisplayPointToGamePoint(Point<int>(ae.mouse.x, ae.mouse.y));
				fxe->data.input.mouse.x = mousepos.x;
				fxe->data.input.mouse.y = mousepos.y;
				forms = true;
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_INPUT_MOUSE_BUTTONDOWN;
				fxe->data.input.mouse.x = ae.mouse.x;
				fxe->data.input.mouse.y = ae.mouse.y;
				fxe->data.input.mouse.deltax = ae.mouse.dx;
				fxe->data.input.mouse.deltay = ae.mouse.dy;
				fxe->data.input.mouse.wheelvertical = ae.mouse.z;
				fxe->data.input.mouse.wheelhorizontal = ae.mouse.w;
				fxe->data.input.mouse.button = ae.mouse.button;
				fxe->data.input.mouse.display = FX->video.FindDisplay( ae.mouse.display );
				mousepos = fxe->data.input.mouse.display->DisplayPointToGamePoint(Point<int>(ae.mouse.x, ae.mouse.y));
				fxe->data.input.mouse.x = mousepos.x;
				fxe->data.input.mouse.y = mousepos.y;
				forms = true;
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_INPUT_MOUSE_BUTTONUP;
				fxe->data.input.mouse.x = ae.mouse.x;
				fxe->data.input.mouse.y = ae.mouse.y;
				fxe->data.input.mouse.deltax = ae.mouse.dx;
				fxe->data.input.mouse.deltay = ae.mouse.dy;
				fxe->data.input.mouse.wheelvertical = ae.mouse.z;
				fxe->data.input.mouse.wheelhorizontal = ae.mouse.w;
				fxe->data.input.mouse.button = ae.mouse.button;
				fxe->data.input.mouse.display = FX->video.FindDisplay( ae.mouse.display );
				mousepos = fxe->data.input.mouse.display->DisplayPointToGamePoint(Point<int>(ae.mouse.x, ae.mouse.y));
				fxe->data.input.mouse.x = mousepos.x;
				fxe->data.input.mouse.y = mousepos.y;
				forms = true;
				break;

			case ALLEGRO_EVENT_JOYSTICK_AXIS:
				break;
			case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
				break;
			case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
				break;

			default:
				break;
		}

		if( fxe != nullptr )
		{
			if( forkb )
			{
				keyboard.OnEvent( fxe );
			}
			if( forms )
			{
				mouse.OnEvent( fxe );
			}
			if( forjs )
			{
			}

			FX->events.PushEvent( fxe );
		}
	}
}

void InputController::RefreshJoysticks()
{
	int joycount = al_get_num_joysticks();
	ALLEGRO_JOYSTICK* curjoy;
	List<Joystick*> toremove;
	bool found;

	// Copy joystick list
	for( int i = 0; i < joysticks.Count(); i++ )
	{
		toremove.Add( joysticks.At( i ) );
	}

	for( int i = 0; i < joycount; i++ )
	{
		curjoy = al_get_joystick( i );
		found = false;
		for( int r = 0; r < toremove.Count(); r++ )
		{
			// Joystick is still attached, delete it from removal queue
			if( toremove.At(r)->joystickref == curjoy )
			{
				toremove.DeleteAt(r);
				found = true;
				break;
			}
		}
		// New joystick, add it
		if( !found )
		{
			joysticks.Add( new Joystick( curjoy ) );
		}
	}

	// Delete joysticks still in removal queue
	for( int r = 0; r < toremove.Count(); r++ )
	{
		for( int i = 0; i < joysticks.Count(); i++ )
		{
			if( toremove.At(r) == joysticks.At(i) )
			{
				joysticks.DeleteAt( i );
				break;
			}
		}
	}
}

#endif // ALLEGRO
