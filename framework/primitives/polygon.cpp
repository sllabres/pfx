
#include "polygon.h"

Polygon::Polygon(List<Point<float>*> Points)
{
	for( int i = 0; i < Points.Count(); i++ )
	{
		points.Add( Points.At(i) );
	}
	Compute();
}

Polygon::Polygon(Point<float>* Points[], int PointCount)
{
	for( int i = 0; i < PointCount; i++ )
	{
		points.Add( Points[i] );
	}
	Compute();
}

Polygon::~Polygon()
{
	while( edges.Count() > 0 )
	{
		delete edges.At(edges.Count() - 1);
		edges.DeleteAt(edges.Count() - 1);
	}
}

void Polygon::Compute()
{
	centre.x = 0;
	centre.y = 0;
	while( edges.Count() > 0 )
	{
		delete edges.At(edges.Count() - 1);
		edges.DeleteAt(edges.Count() - 1);
	}
	for( int i = 0; i < points.Count(); i++ )
	{
		Point<float>* p = points.At( i );
		Point<float>* p2 = points.At( (i + 1) % points.Count() );

		centre.x += p->x;
		centre.y += p->y;
		edges.Add( new Point<float>( p2->x - p->x, p2->y - p->y ) );
	}
	centre.x /= points.Count();
	centre.y /= points.Count();
}

/**********************************************************
		C# code from
		http://www.codeproject.com/Articles/15573/2D-Polyhedron-Collision-Detection
*/
// Calculate the projection of a Polyhedron on an axis and returns it as a [min, max] interval
void Polygon::Project(Point<float> Axis, float* Min, float* Max)
{
	float d = Axis.DotProduct( *points.At(0) );
	*Min = d;
	*Max = d;
	for( int i = 0; i < points.Count(); i++ )
	{
		d = points.At( i )->DotProduct( Axis );
		if( d < *Min )
		{
			*Min = d;
		} else if( d > *Max ) {
			*Max = d;
		}
	}
}

/**********************************************************
		C# code from
		http://www.codeproject.com/Articles/15573/2D-Polyhedron-Collision-Detection
*/
// Calculate the distance between [minA, maxA] and [minB, maxB]
// The distance will be negative if the intervals overlap
float Polygon::IntervalDistance(float MinA, float MaxA, float MinB, float MaxB)
{
	if (MinA < MinB)
	{
		return MinB - MaxA;
	} else {
		return MinA - MaxB;
	}
}

/**********************************************************
		C# code from
		http://www.codeproject.com/Articles/15573/2D-Polyhedron-Collision-Detection
*/
bool Polygon::CollidesWith(Polygon* What, Point<float> Velocity)
{
	bool intersect = true;
	bool willintersect = true;
	int eca = edges.Count();
	int ecb = What->edges.Count();
	Point<float>* edge;

	// Loop through all the edges of both Polyhedrons
	for( int i = 0; i < eca + ecb; i++ )
	{
		if( i < eca )
		{
			edge = edges.At( i );
		} else {
			edge = What->edges.At( i - eca );
		}

		// ===== 1. Find if the Polyhedrons are currently intersecting =====

		// Find the axis perpendicular to the current edge
		Point<float>* axis = new Point<float>(-edge->y, edge->x);
		axis->Normalise();

		// Find the projection of the Polyhedron on the current axis
		float mina = 0; float minb = 0; float maxa = 0; float maxb = 0;
		Project(*axis, &mina, &maxa);
		What->Project(*axis, &minb, &maxb);

		// Check if the Polyhedron projections are currentlty intersecting
		if( IntervalDistance(mina, maxa, minb, maxb) > 0 )
		{
			intersect = false;
		}

		// ===== 2. Now find if the Polyhedrons *will* intersect =====

		// Project the velocity on the current axis
		float vproj = axis->DotProduct( Velocity );

		// Get the projection of Polyhedron A during the movement
		if( vproj < 0 )
		{
			mina += vproj;
		} else {
			maxa += vproj;
		}

		// Do the same test as above for the new projection
		float intervalDistance = IntervalDistance( mina, maxa, minb, maxb );
		if( intervalDistance > 0 )
		{
			willintersect = false;
		}

		delete axis;

		// If the Polyhedrons are not intersecting and won't intersect, exit the loop
		if( !intersect && !willintersect)
		{
			break;
		}

	}

	return (intersect | willintersect);
}

Polygon* Polygon::Translate(Point<float> Offset, bool FlipX, Angle Rotation)
{
	float cos = Rotation.Cosine();
	float sin = Rotation.Sine();
	List<Point<float>*> p;

	for( int i = 0; i < points.Count(); i++ )
	{
		Point<float>* working = new Point<float>( points.At(i)->x * ( FlipX ? -1 : 1 ), points.At(i)->y );

		if( Rotation.degrees != 0.0f )
		{
			float vx = (cos * working->x) - (sin * working->y);
			float vy = (sin * working->x) + (cos * working->y);
			working->x = vx;
			working->y = vy;
		}
		working->x += Offset.x;
		working->y += Offset.y;

		p.Add( working );
	}

	return new Polygon(p);
}

List<Line<float>*>* Polygon::ToLines()
{
	List<Line<float>*>* r = new List<Line<float>*>();

	for( int i = 0; i < points.Count(); i++ )
	{
		Point<float>* p = points.At( i );
		Point<float>* p2 = points.At( (i + 1) % points.Count() );

		r->Add( new Line<float>(*p, *p2) );
	}

	return r;
}

bool Polygon::IsPointInside(Point<float> With)
{
	int i;
	int j;
	bool odd = false;

	j = points.Count() - 1;

	for( i = 0; i < points.Count(); i++ )
	{
		Point<float>* pI = points.At(i);
		Point<float>* pJ = points.At(j);

		if( (pI->y < With.y && pJ->y >= With.y) || (pJ->y < With.y && pI->y >= With.y) )
		{
			if( pI->x + (With.y - pI->y) / (pJ->y - pI->y) * (pJ->x - pI->x) < With.x )
			{
				odd = !odd;
			}
		}

		j = i;
	}

	return odd;
}

bool Polygon::IsPointInside(Point<int> What)
{
	return IsPointInside( Point<float>( (float)What.x, (float)What.y ) );
}
