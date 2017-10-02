
#pragma once

#include "plane_tilemap.h"
#include "atlas_paletted.h"

class PalettedTilemapPlane : public TilemapPlane
{

	protected:
		int* palettemap;
		int* transparentmap;

	public:
		List<Palette*> colourpalettes;

		PalettedTilemapPlane(Display* Owner, PalettedAtlas* TileSet, Size<int> TileSize, Palette* PrimaryPalette, int PrimaryTransparentIndex);
		PalettedTilemapPlane(Display* Owner, PalettedAtlas* TileSet, Size<int> TileSize, Size<int> MapSize, Palette* PrimaryPalette, int PrimaryTransparentIndex);
		~PalettedTilemapPlane();

		void Render() override;

		void SetMapPalette(Point<int> At, int PaletteIndex, int TransparentIndex);
};
