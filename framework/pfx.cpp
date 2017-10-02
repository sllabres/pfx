
#include "pfx.h"

PFx* PFx::FxInst = nullptr;

PFx::PFx()
{
	PFx::FxInst = this;
	frametimerid = -1;
	framestoprocess = 0;
	framespersecond = 0;
	framecontrol = FrameRateControlMethods::DropFrames;
}

PFx::~PFx()
{
}

bool PFx::InitaliseLibraries()
{
	curl_global_init( CURL_GLOBAL_ALL );

#ifdef ALLEGRO
	if( !al_init() )
	{
		return false;
	}
	if( !al_install_keyboard() || !al_install_mouse() || !al_install_joystick() )
	{
		return false;
	}
	if( !al_init_primitives_addon() || !al_init_font_addon() || !al_init_ttf_addon() || !al_init_image_addon() )
	{
		return false;
	}
	if( !al_install_audio() || !al_init_acodec_addon() )
	{
		return false;
	}
	timernextid = 0;
#endif // ALLEGRO

#ifdef SDL1
#endif // SDL1

#ifdef SDL2
#endif // SDL2

	// Some of the controllers need a bootup
	events.Initalise();
	video.Initalise();
	audio.Initalise();
	input.Initalise();

	// Set game rates
	SetFrameRate( 60 );
	SetFrameControl( FrameRateControlMethods::DropFrames );

	return true;
}

void PFx::ShutdownLibraries()
{
	events.Shutdown();
	video.Shutdown();
	input.Shutdown();
	audio.Shutdown();

	curl_global_cleanup();

#ifdef ALLEGRO
	al_uninstall_audio();
	al_uninstall_joystick();
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_system();
#endif // ALLEGRO

#ifdef SDL1
#endif // SDL1

#ifdef SDL2
#endif // SDL2

}

void PFx::Execute(Stage* BootStage)
{
	if( !InitaliseLibraries() )
	{
		return;
	}

	// Load the first stage
	stages.Start( BootStage );

	shutdown = false;

	while( !shutdown )
	{
		// Update all our subsystems
		audio.Update();
		input.Update();
		network.Update();
		downloads.Update();
		video.Update();
		events.Update();	// Import events from underlying system

		// Process the events through the framework
		PumpEvents();

		// Drop out if we're shutting down
		if( shutdown ) { break; }

		while( framestoprocess > 0 )
		{
			// Drop out if we're shutting down
			if( shutdown ) { break; }

			// Drop out if there's no current stage
			Stage* s = stages.Current();
			if( s == nullptr ) { break; }

			// Update stage
			s->Update();
			video.Animate();
			framestoprocess--;
		}

		// Render all the displays
		video.Render();
	}

	ShutdownLibraries();
}

void PFx::PumpEvents()
{
	Event* fxe;
	// Process Events
	fxe = events.Poll();
	while( fxe != nullptr )
	{
		if( stages.Current() == nullptr || fxe->type == EventTypes::EVENT_QUIT )
		{
			Shutdown();
			return;
		} else if( fxe->type == EventTypes::EVENT_VIDEO_CLOSE ) {
			// Allow game to check out the display before closing (and possibly block the close)
			stages.Current()->EventOccured( fxe );
			if( !fxe->handled )
			{
				// Close the display
				video.CloseDisplay( fxe->data.video.display );
				// Quit if we have no more displays
				if( video.GetDisplayCount() == 0 )
				{
					Shutdown();
					return;
				}
			}
		} else if( fxe->type == EventTypes::EVENT_TIMER_TICK ) {
			if( fxe->data.timer.id == frametimerid )
			{
				if( framecontrol == FrameRateControlMethods::DropFrames )
				{
					framestoprocess++;
				} else {
					framestoprocess = 1;
				}

			} else {
				video.EventOccured( fxe );
				stages.Current()->EventOccured( fxe );
			}
		} else if( fxe->type == EventTypes::EVENT_ERROR ) {
			WriteLog( fxe->data.error.functionname, fxe->data.error.message );
			if( fxe->data.error.critical )
			{
				Shutdown();
        return;
			}
		} else if( fxe->type == EventTypes::EVENT_LOG ) {
#ifdef WRITE_LOG
			WriteLog( fxe->data.log.functionname, fxe->data.log.message );
#endif // WRITE_LOG
			stages.Current()->EventOccured( fxe );
		} else {
			video.EventOccured( fxe );
			stages.Current()->EventOccured( fxe );
		}

		fxe = events.Poll();
	}

}

void PFx::Shutdown()
{
	shutdown = true;
}

bool PFx::IsShuttingDown()
{
	return shutdown;
}

void PFx::SetApplicationName(std::string Name)
{
#ifdef ALLEGRO
	al_set_app_name( Name.c_str() );
#endif // ALLEGRO

}

FrameRateControlMethods::FrameRateControlMethod PFx::GetFrameControl()
{
	return framecontrol;
}

void PFx::SetFrameControl(FrameRateControlMethods::FrameRateControlMethod NewMethod)
{
	framecontrol = NewMethod;
}

int PFx::GetFrameRate()
{
	return framespersecond;
}

void PFx::SetFrameRate(int NewRate)
{
	if( frametimerid != -1 )
	{
		if( framespersecond == NewRate )
		{
			return;
		}
		DeleteTimer( frametimerid );
	}

	framespersecond = NewRate;
	frametimerid = CreateTimer( 1.0 / (double)framespersecond );
}

void PFx::WriteLog(std::string* FunctionName, std::string* Message)
{
}

#ifdef ALLEGRO

int PFx::CreateTimer(float IntervalSec)
{
	ALLEGRO_TIMER* t = al_create_timer( IntervalSec );
	int tid = timernextid;
	timers.Add( new IDTag<ALLEGRO_TIMER*>( timernextid, t ) );
	events.RegisterSource( al_get_timer_event_source( t ) );
	timernextid++;
	al_start_timer( t );
	return tid;
}

void PFx::DeleteTimer(int ID)
{
	for( int i = 0; i < timers.Count(); i++ )
	{
		IDTag<ALLEGRO_TIMER*>* id = timers.At( i );
		if( id->id == timernextid )
		{
			al_stop_timer( id->object );
			events.UnregisterSource( al_get_timer_event_source( id->object ) );
			timers.DeleteAt( i );
			break;
		}
	}
}

int PFx::TimerToID(ALLEGRO_TIMER* What)
{
	for( int i = 0; i < timers.Count(); i++ )
	{
		IDTag<ALLEGRO_TIMER*>* id = timers.At( i );
		if( id->object == What )
		{
			return id->id;
		}
	}
	return -1;
}

#endif // ALLEGRO

