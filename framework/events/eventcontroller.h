
#pragma once

#include <mutex>
#include "event.h"
#include "../libraryincludes.h"

class EventController
{

	private:
		List<Event*> events;
		std::mutex eventmutex;

#ifdef ALLEGRO
		ALLEGRO_EVENT_QUEUE* eventqueue;
		List<ALLEGRO_EVENT_SOURCE*> activesources;

		void ProcessAllegroQueue();
#endif // ALLEGRO



	public:
		void Initalise();
		void Shutdown();

		void Update();

		Event* Poll();
		void PushEvent(Event* What);

#ifdef ALLEGRO
		void RegisterSource(ALLEGRO_EVENT_SOURCE* Source);
		void UnregisterSource(ALLEGRO_EVENT_SOURCE* Source);
#endif // ALLEGRO


};
