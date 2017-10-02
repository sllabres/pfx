
#include "colourhsl.h"
#include "colour.h"

ColourHSL::ColourHSL()
{
	h = 0;
	s = 0;
	l = 0;
	a = 0;
}

ColourHSL::ColourHSL(int Hue, unsigned char Saturation, unsigned char Luminance)
{
	h = Hue;
	s = Saturation;
	l = Luminance;
	a = 255;
}

ColourHSL::ColourHSL(int Hue, unsigned char Saturation, unsigned char Luminance, unsigned char Alpha)
{
	h = Hue;
	s = Saturation;
	l = Luminance;
	a = Alpha;
}

Colour ColourHSL::ToRGB()
{
	float fh;
	float fl;
	float fs;
	float t1;
	float t2;
	float t3[3];
	float cl[3];

	while( h < 0 )
	{
		h += 360;
	}
	while( h >= 360 )
	{
		h-= 360;
	}

	if( l == 0 )
	{
		return Colour( 0, 0, 0, a );
	} else if ( s == 0 ) {
		return Colour( l, l, l, a );
	} else {
		fh = h / 359.0f;
		fl = l / 255.0f;
		fs = s / 255.0f;

		t2 = ( fl < 0.5f ? fl * (1.0f + fs) : fl + fs - fl * fs );
		t1 = 2.0f * fl - t2;
		t3[0] = fh + 1.0f / 3.0f;
		t3[1] = fh;
		t3[2] = fh - 1.0f / 3.0f;

		for( int i = 0; i < 3; i++ )
		{
			if( t3[i] < 0 )
			{
				t3[i] += 1.0f;
			}
			if( t3[i] > 1.0f )
			{
				t3[i] -= 1.0f;
			}

			if( 6.0f * t3[i] < 1.0f )
			{
				cl[i] = t1 + (t2 - t1) * t3[i] * 6.0f;
			} else if( 2.0f * t3[i] < 1.0f ) {
				cl[i] = t2;
			} else if( 3.0f * t3[i] < 2.0f ) {
				cl[i] = t1 + (t2 - t1) * (2.0f / 3.0f - t3[i]) * 6.0f;
			} else {
				cl[i] = t1;
			}
		}
		return Colour( (unsigned char)(cl[0] * 255.0f), (unsigned char)(cl[1] * 255.0f), (unsigned char)(cl[2] * 255.0f), a );
	}
}
