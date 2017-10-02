
#include "bitmap.h"

Bitmap::Bitmap(int Width, int Height)
{
	fromexistingsource = false;
	pixelaccess = false;
#ifdef ALLEGRO
	image = al_create_bitmap( Width, Height );

	ALLEGRO_BITMAP* previousrendertarget = al_get_target_bitmap();
	al_set_target_bitmap( image );
	al_clear_to_color( al_map_rgba( 0, 0, 0, 0 ) );
	al_set_target_bitmap( previousrendertarget );
#endif // ALLEGRO
}

Bitmap::Bitmap(std::string Filename)
{
	fromexistingsource = false;
	pixelaccess = false;
#ifdef ALLEGRO
	image = al_load_bitmap( Filename.c_str() );
#endif // ALLEGRO
}


Bitmap::~Bitmap()
{
#ifdef ALLEGRO
	if( !fromexistingsource )
	{
		al_destroy_bitmap( image );
	}
#endif // ALLEGRO
}

Size<int> Bitmap::GetDimensions()
{
	Size<int> d;

#ifdef ALLEGRO
	d.w = al_get_bitmap_width( image );
	d.h = al_get_bitmap_height( image );
#endif // ALLEGRO

	return d;
}


#ifdef ALLEGRO

Bitmap::Bitmap(ALLEGRO_BITMAP* Source)
{
	fromexistingsource = true;
	pixelaccess = false;
	image = Source;
}

void Bitmap::Render(Point<int> At, bool FlipHorizontal, bool FlipVertical)
{
	al_draw_bitmap( image, At.x, At.y, (FlipHorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (FlipVertical ? ALLEGRO_FLIP_VERTICAL : 0) );
}

void Bitmap::RenderRotated(Point<int> At, Point<int> RotationOrigin, Angle Rotation, bool FlipHorizontal, bool FlipVertical)
{
	al_draw_rotated_bitmap(image, RotationOrigin.x, RotationOrigin.y, At.x, At.y, Rotation.ToRadians(), (FlipHorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (FlipVertical ? ALLEGRO_FLIP_VERTICAL : 0) );
}

void Bitmap::RenderPortion(Point<int> At, Rect<int> Region, bool FlipHorizontal, bool FlipVertical)
{
	al_draw_bitmap_region( image, Region.x, Region.y, Region.w, Region.h, At.x, At.y, (FlipHorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (FlipVertical ? ALLEGRO_FLIP_VERTICAL : 0) );
}

void Bitmap::RenderPortion(Point<int> At, Rect<int> Region, bool FlipHorizontal, bool FlipVertical, unsigned char Alpha)
{
	if( Alpha == 0 )
	{
		return;
	}
	if( Alpha == 255 )
	{
		al_draw_bitmap_region( image, Region.x, Region.y, Region.w, Region.h, At.x, At.y, (FlipHorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (FlipVertical ? ALLEGRO_FLIP_VERTICAL : 0) );
	} else {
		al_draw_tinted_bitmap_region( image, al_map_rgba( 255, 255, 255, Alpha ), Region.x, Region.y, Region.w, Region.h, At.x, At.y, (FlipHorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (FlipVertical ? ALLEGRO_FLIP_VERTICAL : 0) );
	}
}

void Bitmap::RenderPortionRotated(Point<int> At, Rect<int> Region, Point<int> RotationOrigin, Angle Rotation, bool FlipHorizontal, bool FlipVertical)
{
	al_draw_tinted_scaled_rotated_bitmap_region( image, Region.x, Region.y, Region.w, Region.h, al_map_rgba_f( 1, 1, 1, 1 ), RotationOrigin.x, RotationOrigin.y, At.x, At.y, 1.0f, 1.0f, Rotation.ToRadians(), (FlipHorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (FlipVertical ? ALLEGRO_FLIP_VERTICAL : 0) );
}

void Bitmap::Render(Point<int> At, Size<float> Scale)
{
	bool fliphorizontal = ( Scale.w < 0 );
	float drawscalew = Maths::Abs( Scale.w );
	bool flipvertical = ( Scale.h < 0 );
	float drawscaleh = Maths::Abs( Scale.h );
	Size<int> imagesize = GetDimensions();
	al_draw_scaled_bitmap( image, 0, 0, imagesize.w, imagesize.h, At.x, At.y, imagesize.w * drawscalew, imagesize.h * drawscaleh, (fliphorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (flipvertical ? ALLEGRO_FLIP_VERTICAL : 0) );
}

void Bitmap::Render(Point<int> At, Size<float> Scale, unsigned char Alpha)
{
	bool fliphorizontal = ( Scale.w < 0 );
	float drawscalew = Maths::Abs( Scale.w );
	bool flipvertical = ( Scale.h < 0 );
	float drawscaleh = Maths::Abs( Scale.h );
	Size<int> imagesize = GetDimensions();
	al_draw_tinted_scaled_bitmap( image, al_map_rgba( 255, 255, 255, Alpha ), 0, 0, imagesize.w, imagesize.h, At.x, At.y, imagesize.w * drawscalew, imagesize.h * drawscaleh, (fliphorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (flipvertical ? ALLEGRO_FLIP_VERTICAL : 0) );
}

void Bitmap::RenderRotated(Point<int> At, Point<int> RotationOrigin, Angle Rotation, Size<float> Scale)
{
	bool fliphorizontal = ( Scale.w < 0 );
	float drawscalew = Maths::Abs( Scale.w );
	bool flipvertical = ( Scale.h < 0 );
	float drawscaleh = Maths::Abs( Scale.h );
	al_draw_scaled_rotated_bitmap(image, RotationOrigin.x, RotationOrigin.y, At.x, At.y, drawscalew, drawscaleh, Rotation.ToRadians(), (fliphorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (flipvertical ? ALLEGRO_FLIP_VERTICAL : 0) );
}

void Bitmap::RenderRotated(Point<int> At, Point<int> RotationOrigin, Angle Rotation, Size<float> Scale, unsigned char Alpha)
{
	if( Alpha == 0 )
	{
		return;
	}

	bool fliphorizontal = ( Scale.w < 0 );
	float drawscalew = Maths::Abs( Scale.w );
	bool flipvertical = ( Scale.h < 0 );
	float drawscaleh = Maths::Abs( Scale.h );

	if( Alpha == 255 )
	{
		al_draw_scaled_rotated_bitmap(image, RotationOrigin.x, RotationOrigin.y, At.x, At.y, drawscalew, drawscaleh, Rotation.ToRadians(), (fliphorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (flipvertical ? ALLEGRO_FLIP_VERTICAL : 0) );
	} else {
		al_draw_tinted_scaled_rotated_bitmap(image, al_map_rgba( 255, 255, 255, Alpha ), RotationOrigin.x, RotationOrigin.y, At.x, At.y, drawscalew, drawscaleh, Rotation.ToRadians(), (fliphorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (flipvertical ? ALLEGRO_FLIP_VERTICAL : 0) );
	}
}

void Bitmap::RenderPortion(Point<int> At, Rect<int> Region, Size<float> Scale)
{
	RenderPortionRotated( At, Region, Point<int>(0, 0), 0, Scale );
}

void Bitmap::RenderPortion(Point<int> At, Rect<int> Region, Size<float> Scale, unsigned char Alpha)
{
	RenderPortionRotated( At, Region, Point<int>(0, 0), 0, Scale, Alpha );
}

void Bitmap::RenderPortionRotated(Point<int> At, Rect<int> Region, Point<int> RotationOrigin, Angle Rotation, Size<float> Scale)
{
	bool fliphorizontal = ( Scale.w < 0 );
	float drawscalew = Maths::Abs( Scale.w );
	bool flipvertical = ( Scale.h < 0 );
	float drawscaleh = Maths::Abs( Scale.h );
	al_draw_tinted_scaled_rotated_bitmap_region( image, Region.x, Region.y, Region.w, Region.h, al_map_rgba_f( 1, 1, 1, 1 ), RotationOrigin.x, RotationOrigin.y, At.x, At.y, drawscalew, drawscaleh, Rotation.ToRadians(), (fliphorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (flipvertical ? ALLEGRO_FLIP_VERTICAL : 0) );
}

void Bitmap::RenderPortionRotated(Point<int> At, Rect<int> Region, Point<int> RotationOrigin, Angle Rotation, Size<float> Scale, unsigned char Alpha)
{
	bool fliphorizontal = ( Scale.w < 0 );
	float drawscalew = Maths::Abs( Scale.w );
	bool flipvertical = ( Scale.h < 0 );
	float drawscaleh = Maths::Abs( Scale.h );
	al_draw_tinted_scaled_rotated_bitmap_region( image, Region.x, Region.y, Region.w, Region.h, al_map_rgba( 255, 255, 255, Alpha ), RotationOrigin.x, RotationOrigin.y, At.x, At.y, drawscalew, drawscaleh, Rotation.ToRadians(), (fliphorizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (flipvertical ? ALLEGRO_FLIP_VERTICAL : 0) );
}


void Bitmap::EnablePixelAccess(bool ReadAccess, bool WriteAccess)
{
	pixelaccess = true;

	int flags = 0;
	if( ReadAccess && WriteAccess )
	{
		flags = ALLEGRO_LOCK_READWRITE;
	} else if( WriteAccess ) {
		flags = ALLEGRO_LOCK_WRITEONLY;
	} else {
		flags = ALLEGRO_LOCK_READONLY;
	}

	lockedarea = GetDimensions();
	pixeldata = al_lock_bitmap( image, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, flags );
}

void Bitmap::EnablePixelAccess(bool ReadAccess, bool WriteAccess, Rect<int> Region)
{
	pixelaccess = true;

	int flags = 0;
	if( ReadAccess && WriteAccess )
	{
		flags = ALLEGRO_LOCK_READWRITE;
	} else if( WriteAccess ) {
		flags = ALLEGRO_LOCK_WRITEONLY;
	} else {
		flags = ALLEGRO_LOCK_READONLY;
	}

	lockedarea.w = Region.w;
	lockedarea.h = Region.h;
	pixeldata = al_lock_bitmap_region( image, Region.x, Region.y, Region.w, Region.h, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, flags );
}

void Bitmap::DisablePixelAccess()
{
	al_unlock_bitmap( image );
	pixelaccess = false;
}

void Bitmap::SetPixel(Point<int> At, Colour NewColour)
{
	SetPixel( At.x, At.y, NewColour );
}

void Bitmap::SetPixel(int AtX, int AtY, Colour NewColour)
{
	if( !pixelaccess )
	{
		return;
	}

	if( AtX < 0 || AtX >= lockedarea.w || AtY < 0 || AtY >= lockedarea.h )
	{
		return;
	}

	void* pxlRaw = (void*)pixeldata->data;
	PackedARGB* pxlValue = (PackedARGB*)( (unsigned long)pxlRaw + (AtY * pixeldata->pitch) + (AtX * pixeldata->pixel_size) );
	pxlValue->r = NewColour.r;
	pxlValue->g = NewColour.g;
	pxlValue->b = NewColour.b;
	pxlValue->a = NewColour.a;

}

Colour Bitmap::GetPixel(Point<int> At)
{
	return GetPixel( At.x, At.y );
}

Colour Bitmap::GetPixel(int AtX, int AtY)
{
	if( !pixelaccess )
	{
		return Colour(0,0,0,0);
	}

	void* pxlRaw = (void*)pixeldata->data;
	PackedARGB* pxlValue = (PackedARGB*)( (unsigned long)pxlRaw + (AtY * pixeldata->pitch) + (AtX * pixeldata->pixel_size) );
	return Colour( pxlValue->r, pxlValue->g, pxlValue->b, pxlValue->a );
}

void Bitmap::ReplaceColour(Colour OldColour, Colour NewColour)
{
	if( !pixelaccess )
	{
		return;
	}
}

void Bitmap::SetAsRenderTarget()
{
	al_set_target_bitmap( image );
}

void Bitmap::Save(std::string Filename)
{
	al_save_bitmap( Filename.c_str(), image );
}

void Bitmap::DrawRectangle(Rect<int> What, Colour DrawColour, int LineWidth)
{
	// al_draw_rectangle( What.Left(), What.Top(), What.Right(), What.Bottom(), al_map_rgba( DrawColour.r, DrawColour.g, DrawColour.b, DrawColour.a ), LineWidth );
	EnablePixelAccess( true, true, What );

	for( int y = 0; y < What.h; y++ )
	{
		SetPixel( 0, y, DrawColour );
		SetPixel( What.w - 1, y, DrawColour );
	}
	for( int x = 0; x < What.w; x++ )
	{
		SetPixel( x, 0, DrawColour );
		SetPixel( x, What.h - 1, DrawColour );
	}

	DisablePixelAccess();
}

void Bitmap::Draw3DRectangle(Rect<int> What, Colour HighlightColour, Colour LowlightColour, int LineWidth, bool Raised)
{
	EnablePixelAccess( true, true, What );

	for( int y = 0; y < What.h; y++ )
	{
		SetPixel( 0, y, (Raised ? HighlightColour : LowlightColour) );
		SetPixel( What.w - 1, y, (Raised ? LowlightColour : HighlightColour) );
	}
	for( int x = 0; x < What.w; x++ )
	{
		SetPixel( x, 0, (Raised ? HighlightColour : LowlightColour) );
		SetPixel( x, What.h - 1, (Raised ? LowlightColour : HighlightColour) );
	}

	DisablePixelAccess();}

void Bitmap::FillRectangle(Rect<int> What, Colour FillColour)
{
	// al_draw_filled_rectangle( What.Left(), What.Top(), What.Right(), What.Bottom(), al_map_rgba( FillColour.r, FillColour.g, FillColour.b, FillColour.a ) );
	EnablePixelAccess( false, true, What );

	for( int y = 0; y < What.h; y++ )
	{
		for( int x = 0; x < What.w; x++ )
		{
			SetPixel( x, y, FillColour );
		}
	}

	DisablePixelAccess();
}

void Bitmap::DrawLine(Line<int> What, Colour DrawColour, int LineWidth)
{
	Size<int> w = GetDimensions();
	// al_draw_line( What.origin.x, What.origin.y, What.destination.x, What.destination.y, al_map_rgba( DrawColour.r, DrawColour.g, DrawColour.b, DrawColour.a ), LineWidth );
	//int lw = Maths::Max( What.origin.x, What.destination.x ) - Maths::Min( What.origin.x, What.destination.x ) + 1;
	//int lh = Maths::Max( What.origin.y, What.destination.y ) - Maths::Min( What.origin.y, What.destination.y ) + 1;
	//EnablePixelAccess( true, true, Rect<int>( Maths::Min( What.origin.x, What.destination.x ), Maths::Min( What.origin.y, What.destination.y ), lw, lh ) );
	EnablePixelAccess( true, true );

	SetPixel( What.origin, DrawColour );
	SetPixel( What.destination, DrawColour );
	for( int l = 1; l < What.Length(); l++ )
	{
		Point<int> s = What.SegmentPoint(l, What.Length());
		SetPixel( s, DrawColour );
	}

	DisablePixelAccess();
}

void Bitmap::DrawEllipses(Ellipses<int> What, Colour DrawColour, int LineWidth)
{
	al_draw_ellipse( What.centre.x, What.centre.y, What.radius.w, What.radius.h, al_map_rgba( DrawColour.r, DrawColour.g, DrawColour.b, DrawColour.a ), LineWidth );
}

void Bitmap::FillEllipses(Ellipses<int> What, Colour FillColour)
{
	al_draw_filled_ellipse( What.centre.x, What.centre.y, What.radius.w, What.radius.h, al_map_rgba( FillColour.r, FillColour.g, FillColour.b, FillColour.a ) );
}

#endif // ALLEGRO

