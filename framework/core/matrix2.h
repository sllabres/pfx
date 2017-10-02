
#pragma once

#include "memory.h"
#include "../primitives/size.h"

template <typename T>
class Matrix2
{

	private:
		Size<int> dimensions;
		T* matrixmap;

	public:

		Matrix2(int Width, int Height)
		{
			dimensions.w = Width;
			dimensions.h = Height;
			matrixmap = (T*)malloc( Width * Height * sizeof( T ) );
			memset( (void*)matrixmap, 0, Width * Height * sizeof( T ) );
		};

		Matrix2(Size<int> Dimensions)
		{
			dimensions = Dimensions;
			matrixmap = (T*)malloc( Dimensions.w * Dimensions.h * sizeof( T ) );
			memset( (void*)matrixmap, 0, Dimensions.w * Dimensions.h * sizeof( T ) );
		};

		void SetValue(int X, int Y, T* Value)
		{
			int ty = Y % dimensions.h;
			while( ty < 0 )
			{
				ty += dimensions.h;
			}
			int tx = X % dimensions.w;
			while( tx < 0 )
			{
				tx += dimensions.w;
			}
			matrixmap[ (ty * dimensions.w) + tx ] = Value;
		};

		T* GetValue(int X, int Y)
		{
			int ty = Y % dimensions.h;
			while( ty < 0 )
			{
				ty += dimensions.h;
			}
			int tx = X % dimensions.w;
			while( tx < 0 )
			{
				tx += dimensions.w;
			}
			return matrixmap[ (ty * dimensions.w) + tx ];
		};

		int GetWidth()
		{
			return dimensions.w;
		};

		int GetHeight()
		{
			return dimensions.h;
		};

};
