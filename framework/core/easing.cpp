
#include "easing.h"

float Easing::EaseOutCubic( float Time, float Begin, float Change, float Duration )
{
	return Change * ((Time = Time / Duration - 1) * Time * Time + 1) + Begin;
}

float Easing::EaseOutQuint( float Time, float Begin, float Change, float Duration )
{
	return Change * ((Time = Time / Duration - 1) * Time * Time * Time * Time + 1) + Begin;
}

float Easing::EaseOutBack( float Time, float Begin, float Change, float Duration, float Swing )
{
	if( Swing == 0)
	{
		Swing = 1.70158f;
	}
	return Change * (( Time = Time / Duration - 1 ) * Time * ( (Swing + 1) * Time + Swing ) + 1) + Begin;
}

float Easing::EaseOutBounce( float Time, float Begin, float Change, float Duration )
{
	if( (Time /= Duration) < (1 / 2.75f) )
	{
		return Change * (7.5625f * Time * Time) + Begin;
	} else if (Time < (2 / 2.75f)) {
		return Change * (7.5625f * (Time -= (1.5f / 2.75f)) * Time + 0.75f) + Begin;
	} else if (Time < (2.5f / 2.75f)) {
		return Change * (7.5625f * (Time -= (2.25f / 2.75f)) * Time + 0.9375f) + Begin;
	} else {
		return Change * (7.5625f * (Time -= (2.625f / 2.75f)) * Time + 0.984375f) + Begin;
	}
}

float Easing::EaseOutElastic( float Time, float Begin, float Change, float Duration )
{
	float swing = 1.70158f;
	float p = 0.0f;
	float a = Change;

	if( Time == 0 )
	{
		return Begin;
	}
	if( (Time /= Duration) == 1 )
	{
		return Begin + Change;
	}
	if( !p )
	{
		p = Duration * 0.3f;
	}

	if( a < Maths::Abs(Change) )
	{
		a = Change;
		swing = p / 4.0f;
	} else {
		swing = p / (2.0f * Maths::Pi()) * asin( Change / a );
	}
	return a * pow(2.0f, -10.0f * Time) * sin( (Time * Duration - swing) * (2.0f * Maths::Pi()) / p ) + Change + Begin;
}

/*
float Easing::EaseInOutExpo( float Time, float Begin, float Change, float Duration )
{
	if( Time == 0 )
	{
		return Begin;
	}

	if( Time == Duration )
	{
		return Begin + Change;
	}

	if( (Time /= Duration / 2) < 1)
	{
		return Change / 2 * pow(2, 10 * (Time - 1)) + Begin;
	}

	return Change / 2 * (-pow(2, -10 * --Time) + 2) + Begin;
}
*/
