
#pragma once

#include "../core/colour.h"
#include "../core/colourhsl.h"
#include "../core/list.h"
#include "display.h"
#include "font.h"
#include "plane_sprites.h"
#include "plane_tilemap_paletted.h"

class VideoController
{

	private:
		List<Display*> displays;

	public:
		bool maintainaspectratio;

		void Initalise();
		void Shutdown();

		int GetMonitorCount();
		Size<int> GetMonitorResolution(int Monitor);

		Display* CreateDisplay(Size<int> GameResolution, int Monitor);
		Display* CreateDisplay(Size<int> GameResolution, int Monitor, Size<int> WindowSize);
		Display* CreateDisplay(Size<int> GameResolution, int Monitor, Size<int> WindowSize, Point<int> WindowPosition);

		void CloseDisplay(Display* What);
		int GetDisplayCount();
		Display* GetDisplay(int Index);
#ifdef ALLEGRO
		Display* FindDisplay(ALLEGRO_DISPLAY* What);
#endif // ALLEGRO
		Bitmap* GetCurrentRenderTargetBitmap();

		void EventOccured(Event* What);
		void Update();
		void Animate();
		void Render();

};
