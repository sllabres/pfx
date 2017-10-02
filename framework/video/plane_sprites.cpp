
#include "plane_sprites.h"

SpritePlane::SpritePlane(Display* Owner) : Plane(Owner)
{
	draworder = SpritePlaneDrawOrder::LIST;
}


void SpritePlane::EventOccured(Event* What)
{
}

void SpritePlane::Update()
{
	for( int i = 0; i < sprites.Count(); i++ )
	{
		sprites.At(i)->Update();
	}
}

void SpritePlane::Render()
{
	IndexSort* is = nullptr;
	Sprite* s;

	switch( draworder )
	{
		case SpritePlaneDrawOrder::LISTREVERSED:
			for( int i = sprites.Count() - 1; i >= 0; i-- )
			{
				sprites.At(i)->position -= scrolloffset;
				sprites.At(i)->Render( alpha );
				sprites.At(i)->position += scrolloffset;
			}
			break;

		case SpritePlaneDrawOrder::XPOSITION:
			is = new IndexSort( sprites.Count() );
			for( int i = 0; i < sprites.Count(); i++ )
			{
				is->SetItem( i, i, sprites.At(i)->position.x );
			}
			is->Sort();
			for( int i = 0; i < sprites.Count(); i++ )
			{
				sprites.At( is->GetIndexAtPosition(i) )->position -= scrolloffset;
				sprites.At( is->GetIndexAtPosition(i) )->Render( alpha );
				sprites.At( is->GetIndexAtPosition(i) )->position += scrolloffset;
			}
			break;

		case SpritePlaneDrawOrder::XPOSITIONREVERSED:
			is = new IndexSort( sprites.Count() );
			for( int i = 0; i < sprites.Count(); i++ )
			{
				is->SetItem( i, i, sprites.At(i)->position.x );
			}
			is->Sort();
			for( int i = sprites.Count() - 1; i >= 0; i-- )
			{
				sprites.At( is->GetIndexAtPosition(i) )->position -= scrolloffset;
				sprites.At( is->GetIndexAtPosition(i) )->Render( alpha );
				sprites.At( is->GetIndexAtPosition(i) )->position += scrolloffset;
			}
			break;

		case SpritePlaneDrawOrder::YPOSITION:
			is = new IndexSort( sprites.Count() );
			for( int i = 0; i < sprites.Count(); i++ )
			{
				is->SetItem( i, i, sprites.At(i)->position.y );
			}
			is->Sort();
			for( int i = 0; i < sprites.Count(); i++ )
			{
				sprites.At( is->GetIndexAtPosition(i) )->position -= scrolloffset;
				sprites.At( is->GetIndexAtPosition(i) )->Render( alpha );
				sprites.At( is->GetIndexAtPosition(i) )->position += scrolloffset;
			}
			break;

		case SpritePlaneDrawOrder::YPOSITIONREVERSED:
			is = new IndexSort( sprites.Count() );
			for( int i = 0; i < sprites.Count(); i++ )
			{
				is->SetItem( i, i, sprites.At(i)->position.y );
			}
			is->Sort();
			for( int i = sprites.Count() - 1; i >= 0; i-- )
			{
				sprites.At( is->GetIndexAtPosition(i) )->position -= scrolloffset;
				sprites.At( is->GetIndexAtPosition(i) )->Render( alpha );
				sprites.At( is->GetIndexAtPosition(i) )->position += scrolloffset;
			}
			break;

		default:
			for( int i = 0; i < sprites.Count(); i++ )
			{
				sprites.At(i)->position -= scrolloffset;
				sprites.At(i)->Render( alpha );
				sprites.At(i)->position += scrolloffset;
			}
			break;
	}

	if( is != nullptr )
	{
		delete is;
	}
}
