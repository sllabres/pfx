
#include "colour.h"
#include "maths.h"

Colour::Colour()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

Colour::Colour(unsigned char Red, unsigned char Green, unsigned char Blue)
{
	r = Red;
	g = Green;
	b = Blue;
	a = 255;
}

Colour::Colour(unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha)
{
	r = Red;
	g = Green;
	b = Blue;
	a = Alpha;
}

ColourHSL Colour::ToHSL()
{
	float fr = r / 255.0f;
	float fg = g / 255.0f;
	float fb = b / 255.0f;
	float cmax = Maths::Max( Maths::Max( fr, fg ), fb );
	float cmin = Maths::Min( Maths::Min( fr, fg ), fb );
	float delta = cmax - cmin;
	float fh = 0;
	float fl = (cmax + cmin) / 2.0f;
	float fs = 0;

	if( delta > 0 )
	{
		if ( cmax == fr ) {
			fh = (fg - fb) / delta;
		} else if ( cmax == fg ) {
			fh = ((fb - fr) / delta) + 2.0f;
		} else if ( cmax == fb ) {
			fh = ((fr - fg) / delta) + 4.0f;
		}
		fs = ( fl < 0.5f ? (delta / (cmax + cmin)) : (delta / (2.0f - cmax - cmin)) );
	}

	return ColourHSL( (int)(fh * 60), (unsigned char)(fs * 255), (unsigned char)(fl * 255), a );
}

Colour Colour::ToGrey()
{
	unsigned char c = (unsigned char)(((float)r * 0.35f) + ((float)g * 0.5f) + ((float)b * 0.15f));
	return Colour( c, c, c );
}

Colour Colour::operator=(Colour With)
{
	a = With.a;
	r = With.r;
	g = With.g;
	b = With.b;
	return *this;
}

Colour Colour::operator=(Colour* With)
{
	a = With->a;
	r = With->r;
	g = With->g;
	b = With->b;
	return *this;
}
