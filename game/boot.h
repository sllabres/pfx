
#pragma once

#include "../framework/pfx.h"

#include "../framework/core/indexsort.h"

class BootUp : public Stage
{

	private:
		int clicks;
		int tickx;
		Display* a;
		SpritePlane* s;
		Sprite* logo;
		Sprite* logomv;
		PingPong<int>* tap;

		Button* b;
		HScrollbar* hs;
		UIPlane* ui;



	public:
		void LoadResources() override;
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Finish() override;
    void EventOccured(Event* What) override;
    void Update() override;
};
