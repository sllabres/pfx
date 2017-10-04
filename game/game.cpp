#include "game.h"

void Game::LoadResources()
{
	display = FX->video.GetDisplay(0);
	spritePlane = new SpritePlane(display);
	spritePlane->draworder = SpritePlaneDrawOrder::YPOSITION;


	background = new Sprite(new Bitmap("resources/main.bmp"));
	background->position.x = display->gameresolution.w / 2;
	background->position.y = display->gameresolution.h / 2;
	background->draworigin.x = background->GetDimensions().w / 2;
	background->draworigin.y = background->GetDimensions().h / 2;
	spritePlane->sprites.Add(background);

	standing = new Animation();
	standing->frames.Add(new AnimationFrame(0, 30));
	standing->frames.Add(new AnimationFrame(1, 30));

	walking = new Animation();
	walking->frames.Add(new AnimationFrame(2, 15));
	walking->frames.Add(new AnimationFrame(3, 15));
	walking->frames.Add(new AnimationFrame(4, 15));

	spinattack = new Animation();
	spinattack->frames.Add(new AnimationFrame(5, 15));
	spinattack->frames.Add(new AnimationFrame(6, 15));
	spinattack->frames.Add(new AnimationFrame(7, 15));
	spinattack->frames.Add(new AnimationFrame(8, 15));
	spinattack->frames.Add(new AnimationFrame(9, 15));

	Size<int> tileSize(barbarianWidth, barbarianHeight);
	Atlas* tiles = new Atlas(new Bitmap("resources/barbarian-tileset.png"), tileSize);
	animatedSprite = new AnimatedSprite(tiles, standing);
	animatedSprite->position.y = display->gameresolution.h - barbarianHeight;
	spritePlane->sprites.Add(animatedSprite);
}

void Game::Start()
{
}

void Game::Pause()
{
}

void Game::Resume()
{
}

void Game::Finish()
{
}

void Game::EventOccured(Event* What)
{
}

void Game::Update()
{
	if (FX->input.keyboard.IsKeyDown(KEYCODE_RIGHT)) {
		animatedSprite->animation = walking;
		if (animatedSprite->position.x < (display->gameresolution.w - barbarianWidth))
			animatedSprite->position.x += 1;
	}
	else if (FX->input.keyboard.IsKeyDown(KEYCODE_LEFT)) {
		animatedSprite->animation = walking;
		if (animatedSprite->position.x > 0)
			animatedSprite->position.x -= 1;
	}
	else if (FX->input.keyboard.IsKeyDown(KEYCODE_SPACE)) {
		animatedSprite->animation = spinattack;
		//FX->CreateTimer()
	}
	else {
		walking->currentframe = 0;
		animatedSprite->animation = standing;
	}
}