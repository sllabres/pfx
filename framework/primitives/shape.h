
#pragma once

#include "point.h"
#include "size.h"
#include "line.h"
#include "../core/list.h"

template <typename T>
class Shape
{

	public:
		virtual List<Line<T>*>* ToLines() = 0;
		virtual bool IsPointInside(Point<T> With) = 0;
		bool IsOverlapping(Shape* With)
		{
			List<Line<T>*> mylines = ToLines();
			List<Line<T>*> withlines = With->ToLines();
			bool foundmatch = false;

			for( int i = 0; i < mylines.Count(); i++ )
			{
				for( int j = 0; j < withlines.Count(); j++ )
				{
					Point<T>* li = mylines.At(i)->IntersectionPoint( withlines.At(j) );
					foundmatch = (li != nullptr);
					if( foundmatch )
					{
						break;
					}
				}				
				if( foundmatch )
				{
					break;
				}
			}

			for( int i = 0; i < mylines.Count(); i++ )
			{
				delete mylines.At(i);
			}
			mylines.Clear();
			for( int j = 0; j < withlines.Count(); j++ )
			{
				delete withlines.At(j);
			}
			withlines.Clear();

			return foundmatch;
		};

};
