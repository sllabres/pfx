
#pragma once

#include "bitmap.h"
#include "../libraryincludes.h"

class Font
{

	private:
#ifdef ALLEGRO
		ALLEGRO_FONT* font;
#endif // ALLEGRO

	public:
		Font(std::string Filename, int PointSize, bool Antialias);
		~Font();

		Bitmap* RenderText(std::string Text, Colour TextColour);
		Bitmap* RenderText(std::string Text, Colour TextColour, int BorderSize, Colour BorderColour);

		void RenderTextInto(Bitmap* Target, Point<int> At, std::string Text, Colour TextColour);
		void RenderTextInto(Bitmap* Target, Point<int> At, std::string Text, Colour TextColour, int BorderSize, Colour BorderColour);

		Size<int> MeasureText(std::string Text);
};
