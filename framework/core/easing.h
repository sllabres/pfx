
#pragma once

#include "maths.h"

// Converted from cheatsheet
// http://easings.net/
// https://github.com/ai/easings.net/blob/master/vendor/jquery.easing.js


class Easing
{

	public:

		static float EaseOutCubic( float Time, float Begin, float Change, float Duration );
		static float EaseOutQuint( float Time, float Begin, float Change, float Duration );
		static float EaseOutBack( float Time, float Begin, float Change, float Duration, float Swing );
		static float EaseOutBounce( float Time, float Begin, float Change, float Duration );
		static float EaseOutElastic( float Time, float Begin, float Change, float Duration );

		// static float EaseInOutExpo( float Time, float Begin, float Change, float Duration );

};
