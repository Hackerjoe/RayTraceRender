#ifndef PLANE_H
#define PLANE_H

#include <math.h>
#include "Ray.h"
#include "Object.h"
#include "Vec.h"
#include "Color.h"

class Plane : public Object{

	Vec normal;
	double distance;
	Color color;

public:
	Plane();

	Plane(Vec norm, double dis, Color Col);

	Vec getPlaneNormal(){ return normal; }

	double getPlaneDistance(){ return distance; }

	virtual Color getColor(){ return color; }

	Vec getNormalAt(Vec point);

	virtual double findIntersection(Ray ray);




};
#endif