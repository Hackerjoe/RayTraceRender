#include "Plane.h"

Plane::Plane()
{
	normal = Vec(1, 0, 0);
	distance = 0;
	color = Color(1, 1, 1, 0);
}

Plane::Plane(Vec norm, double dis, Color Col)
{
	normal = norm;
	distance = dis;
	color = Col;
}

Vec Plane::getNormalAt(Vec point)
{
	return normal;
}

double Plane::findIntersection(Ray ray)
{
	Vec rayDirection = ray.getRayDirection();
	double rayDotNorm = rayDirection.dotProduct(normal);
	if (rayDotNorm == 0)
	{
		//Orthognal
		return -1;
	} else {
		double b = normal.dotProduct(ray.getRayOrgin().addVec(normal.MultiplyVec(distance).negative()));
		return -1 * b / rayDotNorm;

	}
}