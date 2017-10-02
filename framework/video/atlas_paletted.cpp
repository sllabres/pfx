
#include "atlas_paletted.h"
#include "../core/memorystream.h"
#include "../pfx.h"

PalettedAtlas::PalettedAtlas(int Width, int Height, int BitsPerPixel, Memory* Data) : Atlas()
{
	colours = nullptr;
	dimensions.w = Width;
	dimensions.h = Height;
	rawdata = new Memory( Data );
	bpp = BitsPerPixel;
	ConfigureFromData();
}

PalettedAtlas::PalettedAtlas(int Width, int Height, int BitsPerPixel, std::string DataFilename) : Atlas()
{
	colours = nullptr;
	dimensions.w = Width;
	dimensions.h = Height;
	rawdata = new Memory( DataFilename );
	bpp = BitsPerPixel;
	ConfigureFromData();
}

PalettedAtlas::~PalettedAtlas()
{
	free( (void*)drawnstate );
	delete rawdata;
}

void PalettedAtlas::SetPalette(Palette* ColourPalette, int TransparentIndex)
{
	colours = ColourPalette;
	colourtransparent = TransparentIndex;
	memset( (void*)drawnstate, 0, frames.Count() );
}

void PalettedAtlas::Render(Point<int> At, int Frame)
{
	if( drawnstate[Frame] == 0 )
	{
		MemoryStream* ms = new MemoryStream( rawdata );
		ms->Seek( Frame * bytesperimage, MemoryStreamPositions::BEGINNING );

		int c = Frame % cols;
		int r = Frame / cols;

		image->EnablePixelAccess( false, true, Rect<int>(c * dimensions.w, r * dimensions.h, dimensions.w, dimensions.h) );

		for( int y = 0; y < dimensions.h; y++ )
		{
			for( int x = 0; x < dimensions.w; x++ )
			{
				int idx = ms->ReadBits<int>( bpp );
				if( idx == colourtransparent )
				{
					image->SetPixel( x, y, Colour( 0, 0, 0, 0 ) );
				} else {
					image->SetPixel( x, y, *colours->palette.At( idx ) );
				}
			}
		}

		image->DisablePixelAccess();
		delete ms;
		drawnstate[Frame] = 1;
	}
	image->RenderPortion( At, frames.At( Frame ), false, false );
}

void PalettedAtlas::ConfigureFromData()
{
	bytesperimage = Maths::Ceiling( (float)(dimensions.w * dimensions.h * bpp) / 8.0f );
	size_t framecount = rawdata->GetSize() / bytesperimage;

	drawnstate = (char*)malloc( framecount );
	memset( (void*)drawnstate, 0, framecount );

	cols = Maths::Ceiling( sqrtf( (float)framecount ) );
	rows = Maths::Ceiling( framecount / cols );

	image = new Bitmap( cols * dimensions.w, rows * dimensions.h );

	for( int y = 0; y < rows; y++ )
	{
		for( int x = 0; x < cols; x++ )
		{
			frames.Add( new Rect<int>( x * dimensions.w, y * dimensions.h, dimensions.w, dimensions.h ) );
		}
	}

}
