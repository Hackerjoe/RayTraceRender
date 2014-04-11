#include "Sphere.h"

Sphere::Sphere()
{
	center = Vec(0, 0, 0);
	radius = 1.0;
	color = Color(1, 1, 1, 0);

}

Sphere::Sphere(Vec cen, double Rad, Color Col)
{
	center = cen;
	radius = Rad;
	color = Col;
}

double Sphere::findIntersection(Ray ray)
{
	Vec rayOrigin = ray.getRayOrgin();
	double rayOriginX = rayOrigin.getVecX();
	double rayOriginY = rayOrigin.getVecY();
	double rayOriginZ = rayOrigin.getVecZ();

	Vec rayDirection = ray.getRayDirection();
	double rayDirectionX = rayDirection.getVecX();
	double rayDirectionY = rayDirection.getVecY();
	double rayDirectionZ = rayDirection.getVecZ();

	Vec spherCenter = center;
	double sphereCenterX = spherCenter.getVecX();
	double sphereCenterY = spherCenter.getVecY();
	double sphereCenterZ = spherCenter.getVecZ();

	double a = 1; //Normalized
	double b = (2 * (rayOriginX - sphereCenterX)*rayDirectionX) + (2 * (rayOriginY - sphereCenterY)*rayDirectionY) + (2 * (rayOriginZ - sphereCenterZ)*rayDirectionZ);
	double c = pow(rayOriginX - sphereCenterX, 2) + pow(rayOriginY - sphereCenterY, 2) + pow(rayOriginZ - sphereCenterZ, 2) - (radius*radius);

	double discriminant = b*b - 4 * c;

	if (discriminant > 0)
	{
		double root1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.00001;

		if (root1 > 0)
		{
			return root1;
		}
		else
		{
			double root2 = ((sqrt(discriminant) - b) / 2) - 0.00001;
			return root2;
		}
	}
	else
	{
		//Didnt hit sphere
		return -1;
	}
}

Vec Sphere::getNormalAt(Vec point)
{
	Vec normalVec = point.addVec(center.negative()).normalize();
	return normalVec;
}