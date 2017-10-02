
#include "boot.h"

void BootUp::LoadResources()
{
	clicks = 0;

	FX->SetFrameRate( 60 );
	FX->SetFrameControl( FrameRateControlMethods::DropFrames );
	FX->SetApplicationName( "Polymath Framework" );

	Size<int> gameresolution( 800, 480 );
	//a = FX->video.CreateDisplay( gameresolution, 0, Size<int>(1024, 600), Point<int>(0, 0) );
	a = FX->video.CreateDisplay( gameresolution, 0, gameresolution, Point<int>(0, 0) );
	//a = FX->video.CreateDisplay( gameresolution, 0 );

	a->SetTitle( "Polymath Framework" );

	s = new SpritePlane( a );
	s->draworder = SpritePlaneDrawOrder::YPOSITION;
	logo = new Sprite( new Bitmap( "resources/pmprog.png" ) );
	logo->position.x = a->gameresolution.w / 2;
	logo->position.y = a->gameresolution.h / 2;
	logo->draworigin.x = logo->GetDimensions().w / 2;
	logo->draworigin.y = logo->GetDimensions().h / 2;
	s->sprites.Add( logo );

	logomv = new Sprite( new Bitmap( "resources/pmprog.png" ) );
	logomv->position.x = a->gameresolution.w / 2;
	logomv->position.y = a->gameresolution.h / 2;
	logomv->draworigin.x = logomv->GetDimensions().w / 2;
	logomv->draworigin.y = logomv->GetDimensions().h / 2;
	s->sprites.Add( logomv );

	tap = new PingPong<int>(64, 255, 0);
	tap->movestep = 4;
	s->alpha = tap->value;

	ui = new UIPlane( a );
	Form* f = new Form();
	f->position.x = 30;
	f->position.y = 30;
	f->size.w = 320;
	f->size.h = 120;
	f->font = new Font( "resources/inconsolata-regular.ttf", 12, false );
	ui->forms.Add( f );

	Label* fl = new Label( f, "Blar" );
	fl->position.x = 8;
	fl->position.y = 8;
	fl->size.w = 100;
	fl->size.h = 20;
	// fl->font = f->font;

	TextEdit* te = new TextEdit( f, "d" );
	te->position.x = 8;
	te->position.y = 28;
	te->size.w = 100;
	te->size.h = 20;
	te = new TextEdit( f, "vew" );
	te->position.x = 8;
	te->position.y = 48;
	te->size.w = 100;
	te->size.h = 20;

	b = new Button( f, Point<int>(110,8), Size<int>(140, 40), "Press" );

	CheckBox* cb = new CheckBox( f, Point<int>(110, 54), Size<int>(16, 16) );

	hs = new HScrollbar( f, Point<int>( 0, 80 ), Size<int>( 200, 16 ) );
	hs->maximum = 4;

	VScrollbar* vs = new VScrollbar( f, Point<int>( 240, 0 ), Size<int>( 24, 100 ) );
	vs->maximum = 100;
}

void BootUp::Start()
{
	tickx = 0;
}

void BootUp::Pause()
{
}

void BootUp::Resume()
{
}

void BootUp::Finish()
{
}

void BootUp::EventOccured(Event* What)
{
	if( What->type == EventTypes::EVENT_UI_INTERACTION )
	{
		if( What->data.ui.eventtype == FormEventType::ButtonClick )
		{
			clicks++;
		}
		if( What->data.ui.eventtype == FormEventType::CheckBoxChange )
		{
			clicks = 0;
		}
		if( What->data.ui.eventtype == FormEventType::TextChanged )
		{
			clicks = 100;
		}
		if( What->data.ui.eventtype == FormEventType::ScrollBarChange )
		{
			clicks = hs->value;
		}
		b->text = Strings::FromNumber( clicks );
	}
}

void BootUp::Update()
{
	tickx++;
	a->SetTitle( Strings::FromNumber( tickx ) );

	if( FX->input.keyboard.IsKeyDown( KEYCODE_ESC ) )
	{
		FX->Shutdown();
	}

	if( FX->input.keyboard.IsKeyDown( KEYCODE_UP ) )
	{
		logomv->position.y--;
	}
	if( FX->input.keyboard.IsKeyDown( KEYCODE_DOWN ) )
	{
		logomv->position.y++;
	}


	tap->Update();
	s->alpha = tap->value;
	s->scrolloffset.x = (s->scrolloffset.x + 1) % 32;
}
