
#pragma once

#include "../framework/pfx.h"
#include "../framework/core/indexsort.h"
#include "../framework/core/easing.h"

class Game : public Stage
{

private:	
	SpritePlane* spritePlane;	
	Sprite* background;		
	TilemapPlane* tileMap;
	Display* display;

	Animation* standing;
	Animation* walking;
	AnimatedSprite* animatedSprite;
	const int barbarianHeight = 63;
	const int barbarianWidth = 36;

public:
	void LoadResources() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	void Finish() override;
	void EventOccured(Event* What) override;
	void Update() override;
};