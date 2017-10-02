
#include "keyboard.h"
#include "../pfx.h"

Keyboard::Keyboard()
{
	keycodesdepressedcount = 0;
	for( int i = 0; i < PFX_MAX_CONCURRENT_KEYS; i++ )
	{
		keycodesdepressed[i] = 0;
	}
}

void Keyboard::OnEvent(Event* What)
{
	switch( What->type )
	{
		case EventTypes::EVENT_INPUT_KEYBOARD_KEYDOWN:
			if( keycodesdepressedcount < PFX_MAX_CONCURRENT_KEYS )
			{
				keycodesdepressed[keycodesdepressedcount] = What->data.input.keyboard.keycode;
				keycodesdepressedcount++;
			}
			break;
		case EventTypes::EVENT_INPUT_KEYBOARD_KEYUP:
			for( unsigned int i = 0; i < keycodesdepressedcount; i++ )
			{
				if( keycodesdepressed[i] == What->data.input.keyboard.keycode )
				{
					if( i != keycodesdepressedcount - 1)
					{
						keycodesdepressed[i] = keycodesdepressed[keycodesdepressedcount - 1];
					}
					keycodesdepressedcount--;
				}
			}
			break;
		case EventTypes::EVENT_INPUT_KEYBOARD_KEYPRESS:
			break;
		default:
			break;
	}
}

bool Keyboard::IsKeyDown(unsigned int PFxKeyCode)
{
	for( unsigned int i = 0; i < keycodesdepressedcount; i++ )
	{
		if( keycodesdepressed[i] == PFxKeyCode )
		{
			return true;
		}
	}
	return false;
}

void Keyboard::LoadMapping(std::string Filename)
{
}

void Keyboard::SaveMapping(std::string Filename)
{
}

bool Keyboard::IsMappedKeyDown(unsigned int KeyID)
{
	for( int i = 0; i < keymapping.Count(); i++ )
	{
		Point<unsigned int>* map = keymapping.At( i );
		if( map->x == KeyID )
		{
			for( unsigned int i = 0; i < keycodesdepressedcount; i++ )
			{
				if( keycodesdepressed[i] == map->y )
				{
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

void Keyboard::SetKeyMap(unsigned int KeyID, unsigned int PFxKeyCode)
{
	Point<unsigned int>* map = nullptr;
	bool found = false;

	// Can't assign to keyid of 0
	if( KeyID == 0 )
	{
		Event* fxe = new Event();
		fxe->type = EventTypes::EVENT_ERROR;
		fxe->data.error.message = new std::string( "Cannot assign to KeyID 0" );
		fxe->data.error.functionname = new std::string( "Keyboard::SetKeyMap" );
		FX->events.PushEvent( fxe );
		return;
	}

	for( int i = 0; i < keymapping.Count(); i++ )
	{
		map = keymapping.At(i);
		if( map->x == KeyID )
		{
			map->y = PFxKeyCode;
			found = true;
			break;
		}
	}

	if( !found )
	{
		map = new Point<unsigned int>( KeyID, PFxKeyCode );
		keymapping.Add( map );
	}
}

unsigned int Keyboard::GetMappedKeyID(unsigned int PFxKeyCode)
{
	for( int i = 0; i < keymapping.Count(); i++ )
	{
		Point<unsigned int>* map = keymapping.At( i );
		if( map->y == PFxKeyCode )
		{
			return map->x;
		}
	}
	return 0;
}
