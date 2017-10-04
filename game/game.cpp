#include "game.h"

void Game::LoadResources()
{
	Display* display = FX->video.GetDisplay(0);
	spritePlane = new SpritePlane(display);
	spritePlane->draworder = SpritePlaneDrawOrder::YPOSITION;

	/*
	background = new Sprite(new Bitmap("resources/background-main.bmp"));
	background->position.x = display->gameresolution.w / 2;
	background->position.y = display->gameresolution.h / 2;
	background->draworigin.x = background->GetDimensions().w / 2;
	background->draworigin.y = background->GetDimensions().h / 2;
	spritePlane->sprites.Add(background);
	tileMap = new TilemapPlane(display, tiles, tileSize, mapSize);
	tileMap->index0isempty = false;
	tileMap->animations.Add(animation);
	*/


	Size<int> tileSize(36, 63);
	Atlas* tiles = new Atlas(new Bitmap("resources/walk.png"), tileSize);	
	animation = new Animation();	
	//animation->loopanimation = false;
	animation->frames.Add(new AnimationFrame(0, 10));
	animation->frames.Add(new AnimationFrame(1, 10));
	animation->frames.Add(new AnimationFrame(2, 10));
	animation->frames.Add(new AnimationFrame(3, 10));			
	spritePlane->sprites.Add(new AnimatedSprite(tiles, animation));
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
}