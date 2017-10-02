
#pragma once

#include "../events/event.h"

class Stage
{

	public:
		virtual ~Stage() {};

		virtual void LoadResources() = 0;
    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Finish() = 0;
    virtual void EventOccured(Event* What) = 0;
    virtual void Update() = 0;

};
