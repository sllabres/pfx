
#include "eventcontroller.h"
#include "../pfx.h"

void EventController::Initalise()
{
#ifdef ALLEGRO
	eventqueue = al_create_event_queue();
#endif // ALLEGRO


}

void EventController::Shutdown()
{
#ifdef ALLEGRO
	while( activesources.Count() > 0 )
	{
		UnregisterSource( activesources.At( activesources.Count() - 1 ) );
	}
	al_destroy_event_queue( eventqueue );
#endif // ALLEGRO
}

void EventController::Update()
{
#ifdef ALLEGRO
	ProcessAllegroQueue();
#endif // ALLEGRO
}

Event* EventController::Poll()
{
	if( events.Count() == 0 )
	{
		return nullptr;
	} else {
		eventmutex.lock();
		Event* fxe = events.At( 0 );
		events.DeleteAt( 0 );
		eventmutex.unlock();
		return fxe;
	}
}

void EventController::PushEvent(Event* What)
{
	eventmutex.lock();
	events.Add( What );
	eventmutex.unlock();
}

#ifdef ALLEGRO

void EventController::RegisterSource(ALLEGRO_EVENT_SOURCE* Source)
{
	al_register_event_source( eventqueue, Source );
	activesources.Add( Source );
}

void EventController::UnregisterSource(ALLEGRO_EVENT_SOURCE* Source)
{
	al_unregister_event_source( eventqueue, Source );
	activesources.Delete( Source );
}

void EventController::ProcessAllegroQueue()
{
	ALLEGRO_EVENT ae;
	Event* fxe;

	while( al_get_next_event( eventqueue, &ae ) )
	{
		fxe = nullptr;

		switch( ae.type )
		{
			case ALLEGRO_EVENT_TIMER:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_TIMER_TICK;
#ifdef ALLEGRO
				fxe->data.timer.id = FX->TimerToID( ae.timer.source );
				fxe->data.timer.ticks = ae.timer.count;
#endif // ALLEGRO
				break;
			default:
				fxe = new Event();
				fxe->type = EventTypes::EVENT_UNDEFINED;
				break;
		}

		if( fxe != nullptr )
		{
			PushEvent( fxe );
		}
	}

}

#endif // ALLEGRO
