
#include "display.h"
#include "../core/maths.h"
#include "../pfx.h"

Display::Display(Size<int> GameResolution, int Monitor, bool KeepAspectRatio)
{
	gameresolution = GameResolution;
	fullscreen = true;
	keepaspect = KeepAspectRatio;

#ifdef ALLEGRO
	ConfigureDisplayAllegro( GameResolution, Monitor, nullptr, nullptr );
#endif // ALLEGRO

	CalculateScreenScale();
}

Display::Display(Size<int> GameResolution, int Monitor, bool KeepAspectRatio, Size<int> WindowSize)
{
	gameresolution = GameResolution;
	fullscreen = false;
	keepaspect = KeepAspectRatio;

#ifdef ALLEGRO
	ConfigureDisplayAllegro( GameResolution, Monitor, &WindowSize, nullptr );
#endif // ALLEGRO

	CalculateScreenScale();
}

Display::Display(Size<int> GameResolution, int Monitor, bool KeepAspectRatio, Size<int> WindowSize, Point<int> WindowPosition)
{
	gameresolution = GameResolution;
	fullscreen = false;
	keepaspect = KeepAspectRatio;

#ifdef ALLEGRO
	ConfigureDisplayAllegro( GameResolution, Monitor, &WindowSize, &WindowPosition );
#endif // ALLEGRO

	CalculateScreenScale();
}

Display::~Display()
{
	// Destroy all the planes
	for( int i = 0; i < planes.Count(); i++ )
	{
		delete planes.At( i );
	}
	planes.Clear();

#ifdef ALLEGRO
	al_unregister_event_source( eventqueue, al_get_display_event_source( screen ) );
	al_destroy_event_queue( eventqueue );
	al_destroy_display( screen );
#endif // ALLEGRO

}

void Display::EventOccured(Event* What)
{
	for( int i = 0; i < planes.Count(); i++ )
	{
		planes.At( i )->EventOccured( What );
	}
}

void Display::Render()
{
	PreRender();

	for( int i = 0; i < planes.Count(); i++ )
	{
		planes.At( i )->Render();
	}

	PostRender();
}

void Display::CalculateScreenScale()
{
	bestscale = 1.0f;
	if( keepaspect )
	{
		bestscale = Maths::Min( (float)screenresolution.w / (float)gameresolution.w, (float)screenresolution.h / (float)gameresolution.h );
		scalew = gameresolution.w * bestscale;
		scaleh = gameresolution.h * bestscale;
		scalex = (screenresolution.w - scalew) / 2;
		scaley = (screenresolution.h - scaleh) / 2;
	} else {
		scalex = 0;
		scaley = 0;
		scalew = screenresolution.w;
		scaleh = screenresolution.h;
	}
}

Point<int> Display::DisplayPointToGamePoint(Point<int> What)
{
	Point<int> r;

	r.x = (What.x - scalex) / bestscale;
	r.y = (What.y - scaley) / bestscale;
	return r;
}

#ifdef ALLEGRO

void Display::ConfigureDisplayAllegro(Size<int> GameResolution, int Monitor, Size<int>* WindowSize, Point<int>* WindowPosition)
{
	if( fullscreen )
	{
		al_set_new_display_flags( ALLEGRO_FULLSCREEN );
	} else {
		al_set_new_display_flags( ALLEGRO_WINDOWED );
	}
	// al_set_new_display_option( ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST );

	if( fullscreen )
	{
		ALLEGRO_MONITOR_INFO moninfo;
		if( al_get_monitor_info( Monitor, &moninfo ) )
		{
			screenresolution.w = moninfo.x2 - moninfo.x1;
			screenresolution.h = moninfo.y2 - moninfo.y1;
		}
	} else {
		screenresolution.w = WindowSize->w;
		screenresolution.h = WindowSize->h;
	}
	screen = al_create_display( screenresolution.w, screenresolution.h );

	if( screenresolution.w != GameResolution.w || screenresolution.h != GameResolution.h )
	{
		canvas = al_create_bitmap( GameResolution.w, GameResolution.h );
		al_set_target_bitmap( canvas );
	} else {
		canvas = nullptr;
	}

	al_set_blender( ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA );

	al_hide_mouse_cursor( screen );

	if( WindowPosition != nullptr )
	{
		al_set_window_position( screen, WindowPosition->x, WindowPosition->y );
	}

	eventqueue = al_create_event_queue();
	al_register_event_source( eventqueue, al_get_display_event_source( screen ) );

}

void Display::PreRender()
{
	if( canvas == nullptr )
	{
		al_set_target_backbuffer( screen );
	} else {
		al_set_target_bitmap( canvas );
	}
	al_clear_to_color( al_map_rgb( backgroundcolour.r, backgroundcolour.g, backgroundcolour.b ) );
}

void Display::PostRender()
{
	if( canvas != nullptr )
	{
		al_set_target_backbuffer( screen );
		al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
		al_draw_scaled_bitmap( canvas, 0, 0, gameresolution.w, gameresolution.h, scalex, scaley, scalew, scaleh, 0 );

		al_flip_display();

		al_set_target_bitmap( canvas );
	} else {
		al_flip_display();
	}
}

void Display::Update()
{
	ALLEGRO_EVENT ae;
	Event* fxe;

	while( al_get_next_event( eventqueue, &ae ) )
	{
		fxe = nullptr;

		switch( ae.type )
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_VIDEO_CLOSE;
				fxe->data.video.display = this;
				break;
			case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_VIDEO_ACTIVATE;
				fxe->data.video.display = this;
				fxe->data.video.active = true;
				break;
			case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_VIDEO_ACTIVATE;
				fxe->data.video.display = this;
				fxe->data.video.active = false;
				break;
			case ALLEGRO_EVENT_DISPLAY_RESIZE:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_VIDEO_RESIZED;
				fxe->data.video.display = this;
				fxe->data.video.x = ae.display.x;
				fxe->data.video.y = ae.display.y;
				fxe->data.video.width = ae.display.width;
				fxe->data.video.height = ae.display.height;

				al_acknowledge_resize( screen );
				al_get_window_position( screen, &screenlocation.x, &screenlocation.y );
				screenresolution.w = ae.display.width;
				screenresolution.h = ae.display.height;
				CalculateScreenScale();

				break;

			default:
				break;
		}

		if( fxe != nullptr )
		{
			FX->events.PushEvent( fxe );
		}
	}
}

void Display::Animate()
{
	al_get_window_position( screen, &screenlocation.x, &screenlocation.y );
	for( int i = 0; i < planes.Count(); i++ )
	{
		planes.At(i)->Update();
	}
}

void Display::SetTitle(std::string Title)
{
	al_set_window_title( screen, Title.c_str() );
}

void Display::SetAsRenderTarget()
{
	if( canvas != nullptr )
	{
		al_set_target_bitmap( canvas );
	} else {
		al_set_target_backbuffer( screen );
	}
}

void Display::SetMouseCursorVisible(bool Visible)
{
	if( Visible )
	{
		al_show_mouse_cursor( screen );
	} else {
		al_hide_mouse_cursor( screen );
	}
}

#endif // ALLEGRO
