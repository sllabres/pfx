
#include "plane_tilemap_paletted.h"

PalettedTilemapPlane::PalettedTilemapPlane(Display* Owner, PalettedAtlas* TileSet, Size<int> TileSize, Palette* PrimaryPalette, int PrimaryTransparentIndex) : TilemapPlane( Owner, TileSet, TileSize )
{
	colourpalettes.Add( PrimaryPalette );
	palettemap = (int*)malloc( tilemapsize.w * tilemapsize.h * sizeof( int ) );
	memset( (void*)palettemap, 0, tilemapsize.w * tilemapsize.h * sizeof( int ) );
	transparentmap = (int*)malloc( tilemapsize.w * tilemapsize.h * sizeof( int ) );
	memset( (void*)transparentmap, PrimaryTransparentIndex, tilemapsize.w * tilemapsize.h * sizeof( int ) );
}

PalettedTilemapPlane::PalettedTilemapPlane(Display* Owner, PalettedAtlas* TileSet, Size<int> TileSize, Size<int> MapSize, Palette* PrimaryPalette, int PrimaryTransparentIndex) : TilemapPlane( Owner, TileSet, TileSize, MapSize )
{
	colourpalettes.Add( PrimaryPalette );
	palettemap = (int*)malloc( tilemapsize.w * tilemapsize.h * sizeof( int ) );
	memset( (void*)palettemap, 0, tilemapsize.w * tilemapsize.h * sizeof( int ) );
	transparentmap = (int*)malloc( tilemapsize.w * tilemapsize.h * sizeof( int ) );
	memset( (void*)transparentmap, PrimaryTransparentIndex, tilemapsize.w * tilemapsize.h * sizeof( int ) );
}

PalettedTilemapPlane::~PalettedTilemapPlane()
{
	free( palettemap );
	free( transparentmap );
}

void PalettedTilemapPlane::Render()
{
	// Keep scrolloffset relative to the map. Makes things easier
	while( scrolloffset.x < 0 )
	{
		scrolloffset.x += (tilemapsize.w * tilesize.w);
	}
	while( scrolloffset.x >= (tilemapsize.w * tilesize.w) )
	{
		scrolloffset.x -= (tilemapsize.w * tilesize.w);
	}
	while( scrolloffset.y < 0 )
	{
		scrolloffset.y += (tilemapsize.h * tilesize.h);
	}
	while( scrolloffset.y >= (tilemapsize.h * tilesize.h) )
	{
		scrolloffset.y -= (tilemapsize.h * tilesize.h);
	}

	int sx = Maths::Floor( scrolloffset.x / (float)tilesize.w );
	int sy = Maths::Floor( scrolloffset.y / (float)tilesize.h );
	int sw = Maths::Ceiling( owner->gameresolution.w / (float)tilesize.w ) + 1;
	int sh = Maths::Ceiling( owner->gameresolution.h / (float)tilesize.h ) + 1;

	Point<int> renderat;
	renderat.y = -( scrolloffset.y < 0 ? (Maths::Abs( scrolloffset.y ) % tilesize.h) * -1 : (scrolloffset.y % tilesize.h) );

	int lastpalette = -1;

	for( int cury = sy; cury <= sy + sh; cury++ )
	{
		renderat.x = -( scrolloffset.x < 0 ? (Maths::Abs( scrolloffset.x ) % tilesize.w) * -1 : (scrolloffset.x % tilesize.w) );
		for( int curx = sx; curx <= sx + sw; curx++ )
		{
			int tileidx = ((cury % tilemapsize.h) * tilemapsize.w) + (curx % tilemapsize.w);
			if( lastpalette != palettemap[tileidx] )
			{
				((PalettedAtlas*)tileset)->SetPalette( colourpalettes.At( palettemap[tileidx] ), transparentmap[tileidx] );
				lastpalette = palettemap[tileidx];
			}
			tileset->Render( renderat, tilemap[tileidx] );
			renderat.x += tilesize.w;
		}
		renderat.y += tilesize.h;
	}

}

void PalettedTilemapPlane::SetMapPalette(Point<int> At, int PaletteIndex, int TransparentIndex)
{
	int tileidx = (At.y * tilemapsize.w) + At.x;
	if( PaletteIndex < 0 || PaletteIndex >= colourpalettes.Count() )
	{
		palettemap[tileidx] = 0;
		transparentmap[tileidx] = -1;
	} else {
		palettemap[tileidx] = PaletteIndex;
		transparentmap[tileidx] = TransparentIndex;
	}
}

