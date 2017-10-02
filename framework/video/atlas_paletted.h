
#pragma once

#include "atlas.h"
#include "palette.h"

class PalettedAtlas : public Atlas
{

	private:
		Size<int> dimensions;
		int bpp;
		Memory* rawdata;
		size_t bytesperimage;
		Palette* colours;
		int colourtransparent;
		int cols;
		int rows;
		char* drawnstate;

		void ConfigureFromData();

	public:
		PalettedAtlas(int Width, int Height, int BitsPerPixel, Memory* Data);
		PalettedAtlas(int Width, int Height, int BitsPerPixel, std::string DataFilename);

		~PalettedAtlas();

		void SetPalette(Palette* ColourPalette, int TransparentIndex);

		void Render(Point<int> At, int Frame) override;
};
