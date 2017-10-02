
#pragma once

#include <cmath>

#ifndef M_PI
#define M_PI						3.141592654f
#endif

#define M_DEG_TO_RAD		0.01745329f		// (M_PI / 180.0f)
#define M_RAD_TO_DEG		57.2957795f		// (180.0f / M_PI )

class Maths
{
	public:
		static int Min(int A, int B)
		{
			return ( A <= B ? A : B );
		};

		static float Min(float A, float B)
		{
			return ( A <= B ? A : B );
		};

		static int Max(int A, int B)
		{
			return ( A >= B ? A : B );
		};

		static float Max(float A, float B)
		{
			return ( A >= B ? A : B );
		};

		static int Abs(int A)
		{
			return ( A < 0 ? A * -1 : A );
		};

		static float Abs(float A)
		{
			return ( A < 0.0 ? A * -1 : A );
		};

		static float Pi()
		{
			return M_PI;
		}

		static int Floor(float A)
		{
			return (int)A;
		}

		static int Ceiling(float A)
		{
			int fa = Floor(A);
			if( A - fa > 0.0f )
			{
				return fa + 1;
			}
			return fa;
		}

		static int Round(float A)
		{
			float b = (float)A - Floor(A);
			if( b < 0.5f )
			{
				return Floor(A);
			}
			return Ceiling(A);
		}


		// http://stackoverflow.com/users/56338/sth
		// http://stackoverflow.com/questions/2602823/in-c-c-whats-the-simplest-way-to-reverse-the-order-of-bits-in-a-byte
		static unsigned char ReverseBits(unsigned char B)
		{
			B = (B & 0xF0) >> 4 | (B & 0x0F) << 4;
			B = (B & 0xCC) >> 2 | (B & 0x33) << 2;
			B = (B & 0xAA) >> 1 | (B & 0x55) << 1;
			return B;
		}

};
