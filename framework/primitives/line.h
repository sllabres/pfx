
#pragma once

#include "../core/maths.h"
#include "point.h"
#include "angle.h"

template <typename T>
class Line
{
	public:
		Point<T> origin;
		Point<T> destination;

		Line() { origin = Point<T>::Empty(); destination = Point<T>::Empty(); };
		Line(Point<T> O, Point<T> D) { origin = O; destination = D; };
		Line(T OX, T OY, T DX, T DY) { origin = Point<T>(OX, OY); destination = Point<T>(DX, DY); };

		float Length() { T w = origin.x - destination.x; T h = origin.y - destination.y; return sqrt((w*w) + (h*h)); };
		float Slope() { if (origin.x == destination.x) { return 999999999.9999f; } else { return (destination.y - origin.y) / (destination.x - origin.x); } };
		float Intercept() { return origin.y - (Slope() * origin.x); };

		Point<T> SegmentPoint(int Num, int Max) { float x = (destination.x - origin.x) / Max; float y = (destination.y - origin.y) / Max; return Point<T>(origin.x + (x * Num), origin.y + (y * Num)); };

		Point<T>* IntersectionPoint(Line<T> With)
		{
			float lx[2];
			float ly[2];
			float ix[2];
			float iy[2];
			float m[2];
			float b[2];

			lx[0] = (float)origin.x;
			lx[1] = (float)destination.x;
			ly[0] = (float)origin.y;
			ly[1] = (float)destination.y;
			ix[0] = (float)With.origin.x;
			ix[1] = (float)With.destination.x;
			iy[0] = (float)With.origin.y;
			iy[1] = (float)With.destination.y;

			m[0] = Slope();
			m[1] = With.Slope();
			b[0] = Intercept();
			b[1] = With.Intercept();

			float tmp;
			Point<T>* result = nullptr;

			if (lx[0] == lx[1])
			{
				if (Maths::Min(ix[0], ix[1]) <= lx[0] && Maths::Max(ix[0], ix[1]) >= lx[0])
				{
					tmp = (m[1] * lx[0]) + b[1];
					if ((tmp >= ly[0] && tmp <= ly[1]) || (tmp <= ly[0] && tmp >= ly[1]))
					{
						result = new Point<T>((T)lx[0], (T)tmp);
					}
				}
			}
			else if (ix[0] == ix[1]) {
				if (Maths::Min(lx[0], lx[1]) <= ix[0] && Maths::Max(lx[0], lx[1]) >= ix[0])
				{
					tmp = (m[0] * ix[0]) + b[0];
					if ((tmp >= iy[0] && tmp <= iy[1]) || (tmp <= iy[0] && tmp >= iy[1]))
					{
						result = new Point<T>((T)ix[0], (T)tmp);
					}
				}
			}
			else {
				tmp = (b[1] - b[0]) / (m[0] - m[1]);
				if (tmp >= (lx[0] <= lx[1] ? lx[0] : lx[1]) && (lx[0] >= lx[1] ? lx[0] : lx[1]))
				{
					if (tmp >= (ix[0] <= ix[1] ? ix[0] : ix[1]) && (ix[0] >= ix[1] ? ix[0] : ix[1]))
					{
						result = new Point<T>((T)tmp, (T)((m[0] * tmp) + b[0]));
					}
				}
			}

			if ( result != nullptr )
			{
				if (result->x < Maths::Min(origin.x, destination.x) || result->x > Maths::Max(origin.x, destination.x) || result->y < Maths::Min(origin.y, destination.y) || result->y > Maths::Max(origin.y, destination.y) || result->x < Maths::Min(With.origin.x, With.destination.x) || result->x > Maths::Max(With.origin.x, With.destination.x) || result->y < Maths::Min(With.origin.y, With.destination.y) || result->y > Maths::Max(With.origin.y, With.destination.y))
				{
					delete result;
					result = nullptr;
				}
			}

			return result;
		};

		Angle ToAngle() { return Angle( atan2( destination.x - origin.x, origin.y - destination.y ) * M_RAD_TO_DEG ); };
		Angle* Reflection(Line<T> With)
		{
			Point<T>* i = IntersectionPoint( With );
			Angle a;

			if( i == nullptr )
			{
				return nullptr;
			}

			Line<T> li( *i, With.origin );
			Line<T> lc( *i, origin );
			a = li.ToAngle();
			Angle aL = lc.ToAngle() + 90.0f;
			Angle aR = aL + 180.0f;

			if( a.ShortestAngleTo( aL ) < 90.0f )
			{
				if( a.ClockwiseShortestAngleTo( aL ) )
				{
					a += a.ShortestAngleTo( aL ) * 2.0f;
				} else {
					a += a.ShortestAngleTo( aL ) * -2.0f;
				}
			} else {
				if( a.ClockwiseShortestAngleTo( aR ) )
				{
					a += a.ShortestAngleTo( aR ) * 2.0f;
				} else {
					a += a.ShortestAngleTo( aR ) * -2.0f;
				}
			}

			delete i;
			return a;
		};
};
