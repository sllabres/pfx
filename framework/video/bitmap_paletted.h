
#pragma once

#include "../core/memory.h"
#include "bitmap.h"
#include "palette.h"

class PalettedBitmap : public Bitmap
{

	protected:
		int bpp;
		Memory* rawdata;

	public:
		PalettedBitmap(int Width, int Height, int BitsPerPixel);
		PalettedBitmap(int Width, int Height, int BitsPerPixel, Memory* Data);
		PalettedBitmap(int Width, int Height, int BitsPerPixel, std::string DataFilename);

		~PalettedBitmap();

		void SetPalette(Palette* ColourPalette, int TransparentIndex);
		void SetPaletteForRegion(Palette* ColourPalette, int TransparentIndex, Rect<int> Region);


};
