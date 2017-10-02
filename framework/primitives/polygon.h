
#pragma once

#include "../core/list.h"
#include "shape.h"
#include "angle.h"

class Polygon : public Shape<float>
{

	private:
		void Compute();
		void Project(Point<float> Axis, float* Min, float* Max);
		float IntervalDistance(float MinA, float MaxA, float MinB, float MaxB);

	public:
		List<Point<float>*> points;
		List<Point<float>*> edges;
		Point<float> centre;

		Polygon(List<Point<float>*> Points);
		Polygon(Point<float>* Points[], int PointCount);
		~Polygon();

		bool CollidesWith(Polygon* What, Point<float> Velocity);

		Polygon* Translate(Point<float> Offset, bool FlipX, Angle Rotation);

		List<Line<float>*>* ToLines() override;
		bool IsPointInside(Point<float> With) override;
		bool IsPointInside(Point<int> With);

};
