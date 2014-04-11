#include "Light.h"

Light::Light()
{
	Position = Vec(0, 0, 0);
	color = Color(1, 1, 1, 0);
}

Light::Light(Vec Pos, Color Col)
{
	Position = Pos;
	color = Col;
}