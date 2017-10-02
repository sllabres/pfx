
#include "font.h"

Font::Font(std::string Filename, int PointSize, bool Antialias)
{
#ifdef ALLEGRO
	font = al_load_ttf_font( Filename.c_str(), PointSize, (!Antialias ? ALLEGRO_TTF_MONOCHROME : 0) );
#endif // ALLEGRO

}

Font::~Font()
{
#ifdef ALLEGRO
	al_destroy_font( font );
#endif // ALLEGRO

}

Bitmap* Font::RenderText(std::string Text, Colour TextColour)
{
	return RenderText( Text, TextColour, 0, TextColour );
}

void Font::RenderTextInto(Bitmap* Target, Point<int> At, std::string Text, Colour TextColour)
{
	RenderTextInto( Target, At, Text, TextColour, 0, TextColour );
}

#ifdef ALLEGRO

Bitmap* Font::RenderText(std::string Text, Colour TextColour, int BorderSize, Colour BorderColour)
{
	Bitmap* b;

	ALLEGRO_BITMAP* previousrendertarget = al_get_target_bitmap();

	int w = al_get_text_width( font, Text.c_str() ) + (BorderSize * 2);
	int h = al_get_font_line_height( font ) + (BorderSize * 2);
	b = new Bitmap( w, h );
	b->SetAsRenderTarget();
	if( BorderSize > 0 )
	{
		for( int y = 0; y < BorderSize * 2; y++ )
		{
			for( int x = 0; x < BorderSize * 2; x++ )
			{
				al_draw_text( font, al_map_rgba( BorderColour.r, BorderColour.g, BorderColour.b, BorderColour.a ), x, y, 0, Text.c_str() );
			}
		}
	}

	al_draw_text( font, al_map_rgba( TextColour.r, TextColour.g, TextColour.b, TextColour.a ), BorderSize, BorderSize, 0, Text.c_str() );

	al_set_target_bitmap( previousrendertarget );

	return b;
}

void Font::RenderTextInto(Bitmap* Target, Point<int> At, std::string Text, Colour TextColour, int BorderSize, Colour BorderColour)
{
	ALLEGRO_BITMAP* previousrendertarget = al_get_target_bitmap();
	Target->SetAsRenderTarget();

	if( BorderSize > 0 )
	{
		for( int y = 0; y < BorderSize * 2; y++ )
		{
			for( int x = 0; x < BorderSize * 2; x++ )
			{
				al_draw_text( font, al_map_rgba( BorderColour.r, BorderColour.g, BorderColour.b, BorderColour.a ), At.x + x, At.y + y, 0, Text.c_str() );
			}
		}
	}

	al_draw_text( font, al_map_rgba( TextColour.r, TextColour.g, TextColour.b, TextColour.a ), At.x + BorderSize, At.y + BorderSize, 0, Text.c_str() );

	al_set_target_bitmap( previousrendertarget );
}

Size<int> Font::MeasureText(std::string Text)
{
	Size<int> s;
	s.w = al_get_text_width( font, Text.c_str() );
	s.h = al_get_font_line_height( font );
	return s;
}

#endif // ALLEGRO
