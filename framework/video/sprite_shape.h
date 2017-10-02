
#pragma once

#include "sprite.h"
#include "../primitives/shape.h"

template <typename T>
class ShapeSprite : public Sprite
{

	public:
		Shape<T>* shape;
		bool fillshape;
		int borderwidth;
		Colour fillcolour;
		Colour bordercolour;

		ShapeSprite(Shape<T>* DrawShape)
		{
			shape = DrawShape;
			fillshape = false;
			borderwidth = 1;
			fillcolour.a = 255;
			fillcolour.b = 0;
			fillcolour.g = 0;
			fillcolour.r = 0;
			bordercolour.a = 255;
			bordercolour.b = 255;
			bordercolour.g = 255;
			bordercolour.r = 255;
		};

		void Update() override
		{
		};

#ifdef ALLEGRO

		void Render() override
		{
			Render( 255 );
		};

		void Render(unsigned char Alpha) override
		{
			unsigned char alphaval = Maths::Floor( (bordercolour.a / 255.0f) * (float)Alpha );

			List<Line<T>*>* lines = shape->ToLines();

			float* pointmatrix = (float*)malloc( lines->Count() * sizeof( float ) * 2 );

			if( borderwidth > 0 )
			{
				for( int l = 0; l < lines->Count(); l++ )
				{
					Line<T>* ln = lines->At( l );
					//al_draw_line( position.x - draworigin.x + ln->origin.x, position.y - draworigin.y + ln->origin.y, position.x - draworigin.x + ln->destination.x, position.y - draworigin.y + ln->destination.y, al_map_rgba( bordercolour.r, bordercolour.g, bordercolour.b, alphaval ), borderwidth );
					pointmatrix[(l * 2)] = position.x - draworigin.x + ln->origin.x;
					pointmatrix[(l * 2) + 1] = position.y - draworigin.y + ln->origin.y;
				}
				al_draw_polygon( pointmatrix, lines->Count(), ALLEGRO_LINE_JOIN_ROUND, al_map_rgba( bordercolour.r, bordercolour.g, bordercolour.b, alphaval ), borderwidth, 0.5f );
			}
		};

#endif // ALLEGRO

};
