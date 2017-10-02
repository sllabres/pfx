
#pragma once

#include "bitmap_paletted.h"
#include "../core/list.h"

class Atlas
{

	private:
    int gridalloc_size;
		int gridalloc_minx;
		int gridalloc_miny;
		int gridalloc_maxx;
		int gridalloc_maxy;

		List<Bitmap*> subbitmaps;

		void DepackFromGrid( int GridSize );
		void ExtractSpriteFrom( char* Grid, int GridW, int GridH, int StartX, int StartY );
		void AllocateGrid( char* Grid, int GridW, int GridH, int StartX, int StartY );

	protected:
		Atlas();

	public:
		Bitmap* image;
		List<Rect<int>*> frames;

		Atlas(Bitmap* Source);
		Atlas(Bitmap* Source, Size<int> TileSize);
		Atlas(Bitmap* Source, int DepackSpace);

		virtual void Render(Point<int> At, int Frame);
		virtual void Render(Point<int> At, int Frame, unsigned char Alpha);

};
