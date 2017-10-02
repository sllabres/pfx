
#include "plane_tilemap.h"

TilemapPlane::TilemapPlane(Display* Owner, Atlas* TileSet, Size<int> TileSize) : Plane(Owner)
{
	owner = Owner;
	tileset = TileSet;
	tilesize = TileSize;

	index0isempty = true;

	int sw = Maths::Ceiling( owner->gameresolution.w / (float)tilesize.w ) + 1;
	int sh = Maths::Ceiling( owner->gameresolution.w / (float)tilesize.w ) + 1;
	tilemapsize.w = sw;
	tilemapsize.h = sh;
	CreateTilemap();
}

TilemapPlane::TilemapPlane(Display* Owner, Atlas* TileSet, Size<int> TileSize, Size<int> MapSize) : Plane(Owner)
{
	owner = Owner;
	tileset = TileSet;
	tilesize = TileSize;
	scrolloffset.x = 0;
	scrolloffset.y = 0;

	index0isempty = true;

	tilemapsize = MapSize;
	CreateTilemap();

}

TilemapPlane::~TilemapPlane()
{
	free( tilemap );
}

void TilemapPlane::CreateTilemap()
{
	int mapbytes = tilemapsize.w * tilemapsize.h * sizeof( int );
	tilemap = (int*)malloc( mapbytes );
	memset( (void*)tilemap, 0, mapbytes );
}

void TilemapPlane::EventOccured(Event* What)
{
}

void TilemapPlane::Update()
{
	for( int i = 0; i < animations.Count(); i++ )
	{
		animations.At(i)->Animate();
	}
}

void TilemapPlane::Render()
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

#ifdef ALLEGRO
	al_hold_bitmap_drawing( true );
#endif // ALLEGRO

	int sx = Maths::Floor( scrolloffset.x / (float)tilesize.w );
	int sy = Maths::Floor( scrolloffset.y / (float)tilesize.h );
	int sw = Maths::Ceiling( owner->gameresolution.w / (float)tilesize.w ) + 1;
	int sh = Maths::Ceiling( owner->gameresolution.h / (float)tilesize.h ) + 1;

	Point<int> renderat;
	renderat.y = -( scrolloffset.y < 0 ? (Maths::Abs( scrolloffset.y ) % tilesize.h) * -1 : (scrolloffset.y % tilesize.h) );

	for( int cury = sy; cury <= sy + sh; cury++ )
	{
		renderat.x = -( scrolloffset.x < 0 ? (Maths::Abs( scrolloffset.x ) % tilesize.w) * -1 : (scrolloffset.x % tilesize.w) );
		for( int curx = sx; curx <= sx + sw; curx++ )
		{
			int tileidx = ((cury % tilemapsize.h) * tilemapsize.w) + (curx % tilemapsize.w);
			int rendertile = tilemap[tileidx];

			if( rendertile != 0 || !index0isempty )
			{
				if( rendertile < 0 )
				{
					rendertile = animations.At( (rendertile * -1) - 1 )->GetFrameNumber();
				}

				if( alpha == 255 )
				{
					tileset->Render( renderat, rendertile );
				} else {
					tileset->Render( renderat, rendertile, alpha );
				}
			}

			renderat.x += tilesize.w;
		}
		renderat.y += tilesize.h;
	}

#ifdef ALLEGRO
	al_hold_bitmap_drawing( false );
#endif // ALLEGRO
}

int TilemapPlane::GetMapData(Point<int> At)
{
	return tilemap[(At.y * tilemapsize.w) + At.x];
}

void TilemapPlane::SetMapData(Point<int> At, int Frame)
{
	tilemap[(At.y * tilemapsize.w) + At.x] = Frame;
}

