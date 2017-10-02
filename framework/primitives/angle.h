
#pragma once

#include "../core/maths.h"
#include "point.h"

class Angle
{
	private:
		float keepthreesixty() { degrees = keepthreesixty(degrees); return degrees; };
		float keepthreesixty(float A)
		{
			while( A >= 360.0f )
			{
				A -= 360.0f;
			}
			while( A < 0.0f )
			{
				A += 360.0f;
			}
			return A;
		};

	public:
		float degrees;

		static Angle Empty() { return Angle(); };
		static Angle FromRadians(float R) { return Angle(R * M_RAD_TO_DEG); };

		Angle() { degrees = 0; };
		Angle(float A) { degrees = keepthreesixty( A ); };

		bool operator==(Angle Cmp) { return degrees == Cmp.degrees; };
		bool operator!=(Angle Cmp) { return degrees != Cmp.degrees; };
		Angle operator+=(Angle A) { degrees += A.degrees; keepthreesixty(); return *this; };
		Angle operator+=(float A) { degrees += A; keepthreesixty(); return *this; };
		Angle operator-=(Angle A) { degrees -= A.degrees; keepthreesixty(); return *this; };
		Angle operator-=(float A) { degrees -= A; keepthreesixty(); return *this; };
		Angle operator+(Angle A) { return Angle( degrees + A.degrees ); };
		Angle operator+(float A) { return Angle( degrees + A ); };
		Angle operator-(Angle A) { return Angle( degrees - A.degrees ); };
		Angle operator-(float A) { return Angle( degrees - A ); };

		float ToRadians() { return degrees * M_DEG_TO_RAD; };
		float Sine() { return sin(ToRadians()); };
		float Cosine() { return cos(ToRadians()); };
		float Tangent() { return tan(ToRadians()); };
		Point<float> ToVector() { return Point<float>( Sine(), -Cosine() ); };

		float ShortestAngleTo(Angle A) { return Maths::Min( Maths::Abs(A.degrees - degrees), Maths::Abs(degrees - A.degrees) ); };
		float ShortestAngleTo(float A) { return Maths::Min( Maths::Abs(A - degrees), Maths::Abs(degrees - A) ); };
		bool ClockwiseShortestAngleTo(Angle A) { return ClockwiseShortestAngleTo(A.degrees); };
		bool ClockwiseShortestAngleTo(float A) { float d = keepthreesixty(A - degrees); return (d < 180.0f && d > 0.0f); };

};
