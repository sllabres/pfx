#include "title.h"
#include "game.h"

void Title::LoadResources()
{
	FX->SetFrameRate(60);
	FX->SetFrameControl(FrameRateControlMethods::DropFrames);
	FX->SetApplicationName("Polymath Framework");
	Size<int> gameresolution(384, 240);	
	display = FX->video.CreateDisplay(gameresolution, 0, gameresolution, Point<int>(0, 0));
	display->SetTitle("Polymath Framework");
	spritePlane = new SpritePlane(display);
	spritePlane->draworder = SpritePlaneDrawOrder::YPOSITION;
	title = new Sprite(new Bitmap("resources/title.png"));
	title->position.x = display->gameresolution.w / 2;
	title->position.y = display->gameresolution.h / 2;
	title->draworigin.x = title->GetDimensions().w / 2;
	title->draworigin.y = title->GetDimensions().h / 2;
	spritePlane->sprites.Add(title);
	spritePlane->alpha = 0;
	/*FX->audio.AddTrack("resources/main_theme.ogg");
	FX->audio.PlayNextTrack();*/
	FX->CreateTimer(0.1);
}

void Title::Start()
{
	tick = 0;
}

void Title::Pause()
{
}

void Title::Resume()
{
}

void Title::Finish()
{	
	FX->PumpEvents();
	display->planes.Clear();
	delete title;
	delete spritePlane;
}

void Title::EventOccured(Event* What)
{
	if (What->type == EventTypes::EVENT_TIMER_TICK)
	{
		if (tick < 254)
			tick+=2;
	}
}

void Title::Update()
{
	spritePlane->alpha = tick;

	if (FX->input.keyboard.IsKeyDown(KEYCODE_ENTER))
	{		
		FX->stages.Current()->Finish();
		FX->stages.Start(new Game());		
	}
}
