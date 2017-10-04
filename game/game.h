
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
	Animation* spinattack;
	AnimatedSprite* animatedSprite;
	const int barbarianHeight = 67;
	const int barbarianWidth = 70;

public:
	void LoadResources() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	void Finish() override;
	void EventOccured(Event* What) override;
	void Update() override;
};