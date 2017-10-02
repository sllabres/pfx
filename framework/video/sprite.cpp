
#include "sprite.h"

Sprite::Sprite()
{
	image = nullptr;
	atlas = nullptr;
	atlasframe = -1;
	position.x = 0;
	position.y = 0;
	draworigin.x = 0;
	draworigin.y = 0;
	rotation.degrees = 0;
	scale.w = 1;
	scale.h = 1;
}

Sprite::Sprite(Bitmap* Source)
{
	image = Source;
	atlas = nullptr;
	atlasframe = -1;
	position.x = 0;
	position.y = 0;
	draworigin.x = 0;
	draworigin.y = 0;
	rotation.degrees = 0;
	scale.w = 1;
	scale.h = 1;
}

Sprite::Sprite(Atlas* FrameSet, int Frame)
{
	image = FrameSet->image;
	atlas = FrameSet;
	atlasframe = Frame;
	position.x = 0;
	position.y = 0;
	draworigin.x = 0;
	draworigin.y = 0;
	rotation.degrees = 0;
	scale.w = 1;
	scale.h = 1;
}

Size<int> Sprite::GetDimensions()
{
	if( atlas == nullptr || atlasframe < 0 )
	{
		if( image == nullptr )
		{
			return Size<int>(0, 0);
		}
		return image->GetDimensions();
	} else {
		Rect<int>* r = atlas->frames.At(atlasframe);
		return Size<int>( r->w, r->h );
	}
}

void Sprite::Update()
{
}

void Sprite::Render()
{
	if( atlas == nullptr || atlasframe < 0 )
	{
		if( image == nullptr )
		{
			return;
		}
		if( rotation.degrees == 0 )
		{
			image->Render( Point<int>( position.x - (draworigin.x * Maths::Abs(scale.w)), position.y - (draworigin.y * Maths::Abs(scale.h)) ), scale );
		} else {
			image->RenderRotated( position, draworigin, rotation, scale );
		}
	} else {
		Rect<int> rgn = atlas->frames.At(atlasframe);
		if( rotation.degrees == 0 )
		{
			image->RenderPortion( Point<int>( position.x - (draworigin.x * Maths::Abs(scale.w)), position.y - (draworigin.y * Maths::Abs(scale.h)) ), rgn, scale );
		} else {
			image->RenderPortionRotated( position, rgn, draworigin, rotation, scale );
		}
	}
}

void Sprite::Render(unsigned char Alpha)
{
	if( Alpha == 0 )
	{
		return;
	}
	if( Alpha == 255 )
	{
		Render();
		return;
	}
	if( atlas == nullptr || atlasframe < 0 )
	{
		if( image == nullptr )
		{
			return;
		}
		if( rotation.degrees == 0 )
		{
			image->Render( Point<int>( position.x - (draworigin.x * Maths::Abs(scale.w)), position.y - (draworigin.y * Maths::Abs(scale.h)) ), scale, Alpha );
		} else {
			image->RenderRotated( position, draworigin, rotation, scale, Alpha );
		}
	} else {
		Rect<int> rgn = atlas->frames.At(atlasframe);
		if( rotation.degrees == 0 )
		{
			image->RenderPortion( Point<int>( position.x - (draworigin.x * Maths::Abs(scale.w)), position.y - (draworigin.y * Maths::Abs(scale.h)) ), rgn, scale, Alpha );
		} else {
			image->RenderPortionRotated( position, rgn, draworigin, rotation, scale, Alpha );
		}
	}
}
