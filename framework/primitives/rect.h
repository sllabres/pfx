
#pragma once

#include "../core/maths.h"
#include "shape.h"

template <typename T>
class Rect : public Shape<T>
{
	public:
		T x;
		T y;
		T w;
		T h;

		Rect() { x = 0; y = 0; w = 0; h = 0; };
		Rect(T X, T Y, T W, T H) { x = X; y = Y; w = W; h = H; };
		Rect(Point<T> Location, Size<T> Dimensions) { x = Location.x; y = Location.y; w = Dimensions.w; h = Dimensions.h; };
		Rect(Rect<T>* Copy) { x = Copy->x; y = Copy->y; w = Copy->w; h = Copy->h; }

		bool operator==(Rect<T> Cmp) { return (x == Cmp.x) && (y == Cmp.y) && (w == Cmp.w) && (h == Cmp.h); };
		bool operator!=(Rect<T> Cmp) { return (x != Cmp.x) || (y != Cmp.y) || (w != Cmp.w) || (h != Cmp.h); };

		Rect<T> operator=(Rect<T> Val) { x = Val.x; y = Val.y; w = Val.w; h = Val.h; return *this; };
		Rect<T> operator+=(Rect<T> Val) { x += Val.x; y += Val.y; w += Val.w; h += Val.h; return *this; };
		Rect<T> operator-=(Rect<T> Val) { x -= Val.x; y -= Val.y; w -= Val.w; h -= Val.h; return *this; };
		Rect<T> operator*=(Rect<T> Val) { x *= Val.x; y *= Val.y; w *= Val.w; h *= Val.h; return *this; };
		Rect<T> operator/=(Rect<T> Val) { x /= Val.x; y /= Val.y; w /= Val.w; h /= Val.h; return *this; };

		Rect<T> operator+=(Point<T> Val) { x += Val.x; y += Val.y; return *this; };
		Rect<T> operator-=(Point<T> Val) { x -= Val.x; y -= Val.y; return *this; };
		Rect<T> operator*=(Point<T> Val) { x *= Val.x; y *= Val.y; return *this; };
		Rect<T> operator/=(Point<T> Val) { x /= Val.x; y /= Val.y; return *this; };

		Rect<T> operator+=(Size<T> Val) { w += Val.w; h += Val.h; return *this; };
		Rect<T> operator-=(Size<T> Val) { w -= Val.w; h -= Val.h; return *this; };
		Rect<T> operator*=(Size<T> Val) { w *= Val.w; h *= Val.h; return *this; };
		Rect<T> operator/=(Size<T> Val) { w /= Val.w; h /= Val.h; return *this; };

		Rect<T> operator*=(T Val) { x *= Val; y *= Val; w *= Val; h *= Val; return *this; };
		Rect<T> operator/=(T Val) { x /= Val; y /= Val; w /= Val; h /= Val; return *this; };

		T Left() { return Maths::Min( x, x + w ); };
		T Right() { return Maths::Max( x, x + w ); };
		T Top() { return Maths::Min( y, y + h ); };
		T Bottom() { return Maths::Max( y, y + h ); };
		Point<T> Corner(bool CTop, bool CLeft) { return Point<T>( (CLeft ? Left() : Right()), (CTop ? Top() : Bottom()) ); };
		Point<T> Centre() { return Point<T>( x + (w/2), y + (h/2) ); };
		Size<T> GetSize() { return Size<T>( w, h ); };

		List<Line<T>*>* ToLines() override
		{
			List<Line<T>*>* r = new List<Line<T>*>();
			r->Add( new Line<T>( Left(), Top(), Right(), Top() ) );
			r->Add( new Line<T>( Right(), Top(), Right(), Bottom() ) );
			r->Add( new Line<T>( Right(), Bottom(), Left(), Bottom() ) );
			r->Add( new Line<T>( Left(), Bottom(), Left(), Top() ) );
			return r;
		};

		bool IsPointInside(Point<T> With) override
		{
			return (With.x >= x && With.x < x + w && With.y >= y && With.y < y + h);
		};

		// Overloaded for faster Rect checks
		bool IsOverlapping(Rect<T> With) { return (Left() <= With.Right() && Right() <= With.Left() && Top() <= With.Bottom() && Bottom() >= With.Top()); };
};
