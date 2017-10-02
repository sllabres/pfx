
#pragma once

#include "colourhsl.h"

class Colour
{

	private:
		void SetFromHSL(ColourHSL HSL);

	public:
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

		Colour();
		Colour(unsigned char Red, unsigned char Green, unsigned char Blue);
		Colour(unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha);

		ColourHSL ToHSL();
		Colour ToGrey();

		Colour operator=(Colour With);
		Colour operator=(Colour* With);

};
