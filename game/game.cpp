#include "game.h"

void Game::LoadResources()
{
	Display* display = FX->video.GetDisplay(0);
	/*spritePlane = new SpritePlane(display);
	spritePlane->draworder = SpritePlaneDrawOrder::YPOSITION;
	background = new Sprite(new Bitmap("resources/background-main.bmp"));
	background->position.x = display->gameresolution.w / 2;
	background->position.y = display->gameresolution.h / 2;
	background->draworigin.x = background->GetDimensions().w / 2;
	background->draworigin.y = background->GetDimensions().h / 2;	
	spritePlane->sprites.Add(background);*/
	
	

	Atlas* tiles = new Atlas(new Bitmap("resources/barbarian-walk.bmp"));		
	Size<int> tileSize(36, 63);	
	Size<int> mapSize(144, 63);
	animation = new Animation();	
	animation->Start();
	animation->frames.Add(new AnimationFrame(0, 1));
	animation->frames.Add(new AnimationFrame(1, 1));
	animation->frames.Add(new AnimationFrame(2, 1));
	animation->frames.Add(new AnimationFrame(3, 1));
	tileMap = new TilemapPlane(display, tiles, tileSize, mapSize);	
	tileMap->alpha = 255;	
	tileMap->animations.Add(animation);				
	
	
	/*AnimatedSprite* as = new AnimatedSprite(tiles, a);			
	spritePlane->sprites.Add(as);*/
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