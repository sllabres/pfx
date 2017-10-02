
#include "atlas.h"

Atlas::Atlas()
{
}

Atlas::Atlas(Bitmap* Source)
{
	image = Source;
}

Atlas::Atlas(Bitmap* Source, Size<int> TileSize)
{
	image = Source;
	Size<int> isize = image->GetDimensions();
	for( int y = 0; y + TileSize.h <= isize.h; y += TileSize.h )
	{
		for( int x = 0; x + TileSize.w <= isize.w; x += TileSize.w )
		{
			frames.Add( new Rect<int>( x, y, TileSize.w, TileSize.h ) );
		}
	}
}

Atlas::Atlas(Bitmap* Source, int DepackSpace)
{
	image = Source;
	DepackFromGrid( DepackSpace );
}


void Atlas::DepackFromGrid( int GridSize )
{
	Size<int> isize = image->GetDimensions();
	isize.w /= GridSize;
	isize.h /= GridSize;
	gridalloc_size = GridSize;

	char* grid = (char*)malloc( isize.w * isize.h * sizeof(char) );
  memset( (void*)grid, 0, isize.w * isize.h * sizeof(char) );

	image->EnablePixelAccess( true, false );
	for( int gy = 0; gy < isize.h; gy++ )
  {
    for( int gx = 0; gx < isize.w; gx++ )
    {

      for( int y = 0; y < GridSize; y++ )
      {
        for( int x = 0; x < GridSize; x++ )
        {
          int curx = (gx * GridSize) + x;
          int cury = (gy * GridSize) + y;
          Colour c = image->GetPixel( Point<int>(curx, cury) );
          if( c.a != 0 )
          {
            grid[ (gy * isize.w) + gx ] = 1;
            break;
          }
        }
        if( grid[ (gy * isize.w) + gx ] != 0 )
        {
          break;
        }
      }

    }
  }
	image->DisablePixelAccess();

  /*
    Grid is
      0 = Empty Tile
      1 = Populated (not assigned)
      2 = Current Sprite (working)
      3 = Allocated
  */

  for( int gy = 0; gy < isize.h; gy++ )
  {
    for( int gx = 0; gx < isize.w; gx++ )
    {
      if( grid[ (gy * isize.w) + gx ] == 1 )
      {
        ExtractSpriteFrom( grid, isize.w, isize.h, gx, gy );
#ifdef WRITE_LOG
        // FRAMEWORK->WriteLog("SpriteSheet: Depacked (%d, %d, %d, %d)\n", gridalloc_minx, gridalloc_miny, gridalloc_maxx, gridalloc_maxy );
#endif
      }
    }
  }

  free( (void*)grid );
}

void Atlas::ExtractSpriteFrom( char* Grid, int GridW, int GridH, int StartX, int StartY )
{
  // Know where we start
	gridalloc_minx = StartX;
	gridalloc_miny = StartY;
	gridalloc_maxx = StartX;
  gridalloc_maxy = StartY;

  // Follow the grid around for adjactent [1] cells
  AllocateGrid( Grid, GridW, GridH, StartX, StartY );

  // Add sprite to sheet
  frames.Add( new Rect<int>( gridalloc_minx * gridalloc_size, gridalloc_miny * gridalloc_size, ((gridalloc_maxx - gridalloc_minx) + 1) * gridalloc_size, ((gridalloc_maxy - gridalloc_miny) + 1) * gridalloc_size ) );
}

void Atlas::AllocateGrid( char* Grid, int GridW, int GridH, int StartX, int StartY )
{
  // Allocate tile
  Grid[ (StartY * GridW) + StartX ] = 2;
  if( StartX < gridalloc_minx )
  {
    gridalloc_minx = StartX;
  }
  if( StartY < gridalloc_miny )
  {
    gridalloc_miny = StartY;
  }
  if( StartX > gridalloc_maxx )
  {
    gridalloc_maxx = StartX;
  }
  if( StartY > gridalloc_maxy )
  {
    gridalloc_maxy = StartY;
  }

  for( int y = -1; y < 2; y++ )
  {
    for( int x = -1; x < 2; x++ )
    {
      if( y != 0 || x != 0 )
      {

        if( StartX + x >= 0 && StartX + x < GridW && StartY + y >= 0 && StartY + y < GridH )
        {
          // Adjacent tile exists, is it for allocating?
          if( Grid[ ((StartY + y) * GridW) + (StartX + x) ] == 1 )
          {
            AllocateGrid( Grid, GridW, GridH, StartX + x, StartY + y );
          }
        }
      }
    }
  }
}

void Atlas::Render(Point<int> At, int Frame)
{
	image->RenderPortion( At, frames.At( Frame ), false, false );
}

void Atlas::Render(Point<int> At, int Frame, unsigned char Alpha)
{
	image->RenderPortion( At, frames.At( Frame ), false, false, Alpha );
}
