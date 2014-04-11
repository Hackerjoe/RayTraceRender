#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "Vec.h"
#include "Color.h"

class Object{

public:
	Object();

	virtual Color getColor() { return Color(0.0, 1.0, 0.0, 0.0); }

	virtual double findIntersection(Ray ray);



};
#endif