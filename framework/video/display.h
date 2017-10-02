
#pragma once

#include "../primitives/point.h"
#include "../primitives/size.h"
#include "../core/list.h"
#include "../libraryincludes.h"
#include "../core/colour.h"
#include "../events/event.h"

#ifndef Plane
class Plane;
#endif // Plane

class Display
{

	private:
		bool fullscreen;
		bool keepaspect;

		float bestscale;
		int scalex;
		int scaley;
		int scalew;
		int scaleh;

#ifdef ALLEGRO
		ALLEGRO_BITMAP* canvas;
		ALLEGRO_EVENT_QUEUE* eventqueue;

		void ConfigureDisplayAllegro(Size<int> GameResolution, int Monitor, Size<int>* WindowSize, Point<int>* WindowPosition);
#endif // ALLEGRO

#ifdef SDL1
		SDL_Surface* canvas;
#endif // SDL1

#ifdef SDL2
		SDL_Surface* canvas;
#endif // SDL2

		void PreRender();
		void PostRender();
		void CalculateScreenScale();

	public:
#ifdef ALLEGRO
		ALLEGRO_DISPLAY* screen;
#endif // ALLEGRO

		Size<int> gameresolution;
		Point<int> screenlocation;
		Size<int> screenresolution;
		Colour backgroundcolour;

		List<Plane*> planes;

		Display(Size<int> GameResolution, int Monitor, bool KeepAspectRatio);
		Display(Size<int> GameResolution, int Monitor, bool KeepAspectRatio, Size<int> WindowSize);
		Display(Size<int> GameResolution, int Monitor, bool KeepAspectRatio, Size<int> WindowSize, Point<int> WindowPosition);

		~Display();

		void EventOccured(Event* What);
		void Update();
		void Animate();
		void Render();

		void SetTitle(std::string Title);
		void SetAsRenderTarget();
		void SetMouseCursorVisible(bool Visible);

		Point<int> DisplayPointToGamePoint(Point<int> What);

		bool IsFullscreen() { return fullscreen; };

};
