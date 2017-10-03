
#pragma once

#include "../framework/pfx.h"
#include "../framework/core/indexsort.h"
#include "../framework/core/easing.h"

class BootUp : public Stage
{

private:
	Display* display;
	SpritePlane* spritePlane;	
	Sprite* title;
	Easing* ease;
	unsigned char tick;

public:
	void LoadResources() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	void Finish() override;
	void EventOccured(Event* What) override;
	void Update() override;
};
