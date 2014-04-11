#ifndef VEC_H
#define VEC_H
#include <math.h>

class Vec{
private:
	double x, y, z;

public:
	Vec();

	Vec(double X,double Y,double Z);

	double getVecX() { return x; }
	double getVecY() { return y; }
	double getVecZ() { return z; }

	Vec normalize();

	double magnitude();

	Vec negative();

	double dotProduct(Vec v);

	Vec crossProduct(Vec v);

	Vec addVec(Vec v);

	Vec MultiplyVec(double scalar);

};
#endif