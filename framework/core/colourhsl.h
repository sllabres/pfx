
#pragma once

#ifndef Colour
class Colour;
#endif // Colour

class ColourHSL
{
	public:
		int h;
		unsigned char s;
		unsigned char l;
		unsigned char a;

		ColourHSL();
		ColourHSL(int Hue, unsigned char Saturation, unsigned char Luminance);
		ColourHSL(int Hue, unsigned char Saturation, unsigned char Luminance, unsigned char Alpha);

		Colour ToRGB();
};
