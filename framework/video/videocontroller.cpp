
#include "videocontroller.h"
#include "../libraryincludes.h"

void VideoController::Initalise()
{
	maintainaspectratio = true;
}

void VideoController::Shutdown()
{
	while( displays.Count() > 0 )
	{
		Display* d = displays.At( displays.Count() - 1 );
		displays.DeleteAt( displays.Count() - 1 );
		delete d;
	}
}

Display* VideoController::CreateDisplay(Size<int> GameResolution, int Monitor)
{
	Display* d = new Display( GameResolution, Monitor, maintainaspectratio );
	displays.Add( d );
	return d;
}

Display* VideoController::CreateDisplay(Size<int> GameResolution, int Monitor, Size<int> WindowSize)
{
	Display* d = new Display( GameResolution, Monitor, maintainaspectratio, WindowSize );
	displays.Add( d );
	return d;
}

Display* VideoController::CreateDisplay(Size<int> GameResolution, int Monitor, Size<int> WindowSize, Point<int> WindowPosition)
{
	Display* d = new Display( GameResolution, Monitor, maintainaspectratio, WindowSize, WindowPosition );
	displays.Add( d );
	return d;
}

void VideoController::CloseDisplay(Display* What)
{
	displays.Delete( What );
	delete What;
}

int VideoController::GetDisplayCount()
{
	return displays.Count();
}

Display* VideoController::GetDisplay(int Index)
{
	return displays.At( Index );
}

void VideoController::EventOccured(Event* What)
{
	for( int i = 0; i < displays.Count(); i++ )
	{
		displays.At( i )->EventOccured( What );
	}
}

void VideoController::Update()
{
	for( int i = 0; i < displays.Count(); i++ )
	{
		displays.At( i )->Update();
	}
}

void VideoController::Animate()
{
	for( int i = 0; i < displays.Count(); i++ )
	{
		displays.At( i )->Animate();
	}
}

void VideoController::Render()
{
	for( int i = 0; i < displays.Count(); i++ )
	{
		displays.At( i )->Render();
	}
}

#ifdef ALLEGRO

int VideoController::GetMonitorCount()
{
	return al_get_num_video_adapters();
}

Size<int> VideoController::GetMonitorResolution(int Monitor)
{
	Size<int> s;
	ALLEGRO_MONITOR_INFO moninfo;
	if( al_get_monitor_info( Monitor, &moninfo ) )
	{
		s.w = moninfo.x2 - moninfo.x1;
		s.h = moninfo.y2 - moninfo.y1;
	}
	return s;
}

Display* VideoController::FindDisplay(ALLEGRO_DISPLAY* What)
{
	for( int i = 0; i < displays.Count(); i++ )
	{
		Display* d = displays.At( i );
		if( d->screen == What )
		{
			return d;
		}
	}
	return nullptr;
}

Bitmap* VideoController::GetCurrentRenderTargetBitmap()
{
	return new Bitmap( al_get_target_bitmap() );
}

#endif // ALLEGRO