#ifndef RAY_H
#define RAY_H

#include <math.h>
#include "Vec.h"

class Ray{

	Vec Origin, Direction;

public:
	Ray();

	Ray(Vec or, Vec dir);

	Vec getRayOrgin() { return Origin; }
	Vec getRayDirection() { return Direction; }


};
#endif