
#pragma once

#include <math.h>

template <typename T>
class Point
{
	public:
		T x;
		T y;

		static Point<T> Empty() { return Point<T>(); };

		Point() { x = 0; y = 0; };
		Point(T X, T Y) { x = X; y = Y; };

		bool operator==(Point<T> Cmp) { return (x == Cmp.x) && (y == Cmp.y); };
		bool operator!=(Point<T> Cmp) { return (x != Cmp.x) || (y != Cmp.y); };
		Point<T> operator=(Point<T> Val) { x = Val.x; y = Val.y; return *this; };
		Point<T> operator+=(Point<T> Val) { x = x + Val.x; y = y + Val.y; return *this; };
		Point<T> operator-=(Point<T> Val) { x = x - Val.x; y = y - Val.y; return *this; };
		Point<T> operator*=(Point<T> Val) { x = x * Val.x; y = y * Val.y; return *this; };
		Point<T> operator*=(T Val) { x = x * Val; y = y * Val; return *this; };
		Point<T> operator/=(Point<T> Val) { x = x / Val.x; y = y / Val.y; return *this; };
		Point<T> operator/=(T Val) { x = x / Val; y = y / Val; return *this; };

		float DotProduct(Point<T> With) { return (x * With.x) + (y * With.y); };

		void Normalise() { float m = sqrt( (x*x) + (y*y) ); x /= m; y /= m; };
};
