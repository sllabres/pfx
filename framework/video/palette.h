
#pragma once

#include "../core/colour.h"
#include "../core/list.h"

#define PALETTE_C64_COLOUR_INDEX_BLACK        0
#define PALETTE_C64_COLOUR_INDEX_WHITE        1
#define PALETTE_C64_COLOUR_INDEX_RED          2
#define PALETTE_C64_COLOUR_INDEX_CYAN         3
#define PALETTE_C64_COLOUR_INDEX_PURPLE       4
#define PALETTE_C64_COLOUR_INDEX_GREEN        5
#define PALETTE_C64_COLOUR_INDEX_BLUE         6
#define PALETTE_C64_COLOUR_INDEX_YELLOW       7
#define PALETTE_C64_COLOUR_INDEX_ORANGE       8
#define PALETTE_C64_COLOUR_INDEX_BROWN        9
#define PALETTE_C64_COLOUR_INDEX_PINK         10
#define PALETTE_C64_COLOUR_INDEX_DARK_GRAY    11
#define PALETTE_C64_COLOUR_INDEX_MID_GRAY     12
#define PALETTE_C64_COLOUR_INDEX_LIGHT_GREEN  13
#define PALETTE_C64_COLOUR_INDEX_LIGHT_BLUE   14
#define PALETTE_C64_COLOUR_INDEX_LIGHT_GRAY   15

#define PALETTE_ARNE_COLOUR_INDEX_BLACK        0
#define PALETTE_ARNE_COLOUR_INDEX_LIGHT_GRAY   1
#define PALETTE_ARNE_COLOUR_INDEX_WHITE        2
#define PALETTE_ARNE_COLOUR_INDEX_RED          3
#define PALETTE_ARNE_COLOUR_INDEX_PINK         4
#define PALETTE_ARNE_COLOUR_INDEX_DARK_BROWN   5
#define PALETTE_ARNE_COLOUR_INDEX_BROWN        6
#define PALETTE_ARNE_COLOUR_INDEX_ORANGE       7
#define PALETTE_ARNE_COLOUR_INDEX_DARK_GRAY    8
#define PALETTE_ARNE_COLOUR_INDEX_MID_GRAY     9
#define PALETTE_ARNE_COLOUR_INDEX_GREEN        10
#define PALETTE_ARNE_COLOUR_INDEX_LIGHT_GREEN  11
#define PALETTE_ARNE_COLOUR_INDEX_YELLOW       12
#define PALETTE_ARNE_COLOUR_INDEX_BLUE         13
#define PALETTE_ARNE_COLOUR_INDEX_LIGHT_BLUE   14
#define PALETTE_ARNE_COLOUR_INDEX_CYAN         15


class PaletteFixed
{
	public:
		enum PaletteOptions
		{
			C64,
			ARNE16
		};
};

class Palette
{

	public:
		List<Colour*> palette;

		Palette();
		Palette(PaletteFixed::PaletteOptions Option);
		Palette(std::string Filename);

		void SavePalette(std::string Filename);

};
