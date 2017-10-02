
#include "mouse.h"
#include "../pfx.h"

Mouse::Mouse()
{
	for(int i = 0; i < PFX_MAX_MOUSE_BUTTONS; i++ )
	{
		buttonsdown[i] = false;
	}
}

void Mouse::OnEvent(Event* What)
{
	switch( What->type )
	{
		case EventTypes::EVENT_INPUT_MOUSE_MOVE:
			position.x = What->data.input.mouse.x;
			position.y = What->data.input.mouse.y;
			wheelvertical = What->data.input.mouse.wheelvertical;
			wheelhorizontal = What->data.input.mouse.wheelhorizontal;
			activedisplay = What->data.input.mouse.display;
			break;
		case EventTypes::EVENT_INPUT_MOUSE_BUTTONDOWN:
			if( What->data.input.mouse.button >= 0 && What->data.input.mouse.button < PFX_MAX_MOUSE_BUTTONS )
			{
				buttonsdown[What->data.input.mouse.button] = true;
			}
			activedisplay = What->data.input.mouse.display;
			break;
		case EventTypes::EVENT_INPUT_MOUSE_BUTTONUP:
			if( What->data.input.mouse.button >= 0 && What->data.input.mouse.button < PFX_MAX_MOUSE_BUTTONS )
			{
				buttonsdown[What->data.input.mouse.button] = false;
			}
			activedisplay = What->data.input.mouse.display;
			break;
		default:
			break;
	}
}

bool Mouse::IsButtonDown(int ButtonNumber)
{
	if( ButtonNumber < 0 || ButtonNumber >= PFX_MAX_MOUSE_BUTTONS )
	{
		return false;
	}
	return buttonsdown[ButtonNumber];
}

Display* Mouse::GetActiveDisplay()
{
	return activedisplay;
}

#ifdef ALLEGRO

int Mouse::GetButtonCount()
{
	return al_get_mouse_num_buttons();
}

void Mouse::Warp(Point<int> Position)
{
	al_set_mouse_xy( activedisplay->screen, Position.x, Position.y );
}

#endif // ALLEGRO
