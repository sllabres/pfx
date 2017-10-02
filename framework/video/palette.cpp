
#include "palette.h"

Palette::Palette()
{
}

Palette::Palette(PaletteFixed::PaletteOptions Option)
{
	switch( Option )
	{
		case PaletteFixed::C64:
			palette.Add( new Colour(   0,   0,   0 ) );
			palette.Add( new Colour( 255, 255, 255 ) );
			palette.Add( new Colour( 104,  55,  43 ) );
			palette.Add( new Colour( 112, 164, 178 ) );
			palette.Add( new Colour( 111,  61, 134 ) );
			palette.Add( new Colour(  88, 141,  67 ) );
			palette.Add( new Colour(  53,  40, 121 ) );
			palette.Add( new Colour( 184, 199, 111 ) );
			palette.Add( new Colour( 111,  79,  37 ) );
			palette.Add( new Colour(  67,  57,   0 ) );
			palette.Add( new Colour( 154, 103,  89 ) );
			palette.Add( new Colour(  68,  68,  68 ) );
			palette.Add( new Colour( 108, 108, 108 ) );
			palette.Add( new Colour( 154, 210, 132 ) );
			palette.Add( new Colour( 108,  94, 181 ) );
			palette.Add( new Colour( 149, 149, 149 ) );
			break;
		case PaletteFixed::ARNE16:
			palette.Add( new Colour(   0,   0,   0 ) );
			palette.Add( new Colour( 157, 157, 157 ) );
			palette.Add( new Colour( 255, 255, 255 ) );
			palette.Add( new Colour( 190,  38,  51 ) );
			palette.Add( new Colour( 224, 111, 139 ) );
			palette.Add( new Colour(  73,  60,  43 ) );
			palette.Add( new Colour( 164, 100,  34 ) );
			palette.Add( new Colour( 235, 137,  49 ) );
			palette.Add( new Colour(  27,  38,  50 ) );
			palette.Add( new Colour(  47,  72,  78 ) );
			palette.Add( new Colour(  68, 137,  26 ) );
			palette.Add( new Colour( 163, 206,  39 ) );
			palette.Add( new Colour( 247, 226, 107 ) );
			palette.Add( new Colour(   0,  87, 132 ) );
			palette.Add( new Colour(  49, 162, 242 ) );
			palette.Add( new Colour( 178, 220, 239 ) );
			break;
	}
}

Palette::Palette(std::string Filename)
{
}

void Palette::SavePalette(std::string Filename)
{
}
