#include "Vec.h"


Vec::Vec()
{
	x = 0;
	y = 0;
	z = 0;
}

Vec::Vec(double X, double Y, double Z)
{
	x = X;
	y = Y;
	z = Z;
}

double Vec::magnitude()
{
	return sqrt((x*x) + (y*y) + (z*z));
}

Vec Vec::normalize()
{
	double magnitude = sqrt((x*x) + (y*y) + (z*z));
	return Vec(x / magnitude, y / magnitude, z / magnitude);
}
Vec Vec::negative()
{
	return Vec(-x, -y, -z);
}

double Vec::dotProduct(Vec v)
{
	return x*v.getVecX() + y*v.getVecY() + z*v.getVecZ();
}

Vec Vec::crossProduct(Vec v)
{
	return Vec(y*v.getVecZ() - z*v.getVecY(), z*v.getVecX() - x*v.getVecZ(), x*v.getVecY() - y*v.getVecX());
}

Vec Vec::addVec(Vec v)
{
	return Vec(x +v.getVecX(), y + v.getVecY(), z + v.getVecZ());
}

Vec Vec::MultiplyVec(double scalar)
{
	return Vec(x*scalar,y*scalar,z*scalar);
}