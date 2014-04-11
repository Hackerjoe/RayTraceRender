#ifndef LIGHT_H
#define LIGHT_H

#include "Vec.h"
#include "Color.h"

class Light{

	Vec Position;
	Color color;
public:
	Light();

	Light(Vec Pos, Color Col);

	Vec getLightPos(){ return Position; }

	Color getLightColor(){ return color; }



};
#endif