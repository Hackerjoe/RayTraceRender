#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include "Object.h"
#include "Vec.h"
#include "Color.h"
#include "Ray.h"

class Sphere: public Object{

	Vec center;
	double radius;
	Color color;

public:
	Sphere();

	Sphere(Vec cen, double Rad, Color Col);

	Vec getSphereCenter(){ return center; }

	double getSphereRadius(){ return radius; }

	virtual Color getColor(){ return color; }

	Vec getNormalAt(Vec point);

	virtual double findIntersection(Ray ray);




};
#endif