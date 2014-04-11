#include "Ray.h"


Ray::Ray()
{
	Origin = Vec(0, 0, 0);
	Direction = Vec(1, 0, 0);
}

Ray::Ray(Vec or, Vec dir)
{
	Origin = or;
	Direction = dir;
}