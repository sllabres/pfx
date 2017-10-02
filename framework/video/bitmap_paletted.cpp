
#include "bitmap_paletted.h"
#include "../pfx.h"

PalettedBitmap::PalettedBitmap(int Width, int Height, int BitsPerPixel) : Bitmap( Width, Height )
{
	bpp = BitsPerPixel;
	rawdata = new Memory( Maths::Ceiling( (float)(Width * Height * bpp) / 8.0f ) );
}

PalettedBitmap::PalettedBitmap(int Width, int Height, int BitsPerPixel, Memory* Data) : Bitmap( Width, Height )
{
	bpp = BitsPerPixel;
	rawdata = new Memory( Data );
}

PalettedBitmap::PalettedBitmap(int Width, int Height, int BitsPerPixel, std::string DataFilename) : Bitmap( Width, Height )
{
	bpp = BitsPerPixel;
	rawdata = new Memory( DataFilename );
	if( rawdata->GetSize() < (size_t)Maths::Ceiling( (float)(Width * Height * bpp) / 8.0f ) )
	{
		// Error!
		FX->events.PushEvent( Event::ErrorEvent( "PalettedBitmap::PalettedBitmap", "Data file '" + DataFilename + "' does not contain enough data to match WxHxBPP", false ) );		
		delete rawdata;
		rawdata = new Memory( Maths::Ceiling( (float)(Width * Height * bpp) / 8.0f ) );
	}
}

PalettedBitmap::~PalettedBitmap()
{
	delete rawdata;
}

void PalettedBitmap::SetPalette(Palette* ColourPalette, int TransparentIndex)
{
	SetPaletteForRegion( ColourPalette, TransparentIndex, Rect<int>( 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image) ) );
}

void PalettedBitmap::SetPaletteForRegion(Palette* ColourPalette, int TransparentIndex, Rect<int> Region)
{
	MemoryStream* ms = new MemoryStream( rawdata );
	EnablePixelAccess( false, true );

	for( int y = Region.y; y < Region.h; y++ )
	{
		for( int x = Region.x; x < Region.w; x++ )
		{
			int idx = ms->ReadBits<int>( bpp );
			if( idx == TransparentIndex )
			{
				SetPixel( x, y, Colour( 0, 0, 0, 0 ) );
			} else {
				SetPixel( x, y, *ColourPalette->palette.At( idx ) );
			}
		}
	}

	DisablePixelAccess();
	delete ms;
}
