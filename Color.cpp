#include "Color.h"

Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
	a = 0;
}

Color::Color(double r, double g, double b, double a)
{
	red = r;
	green = g;
	blue = b;
	a = a;
}

void Color::setColor(double r, double g, double b, double a)
{
	red = r;
	green = g;
	blue = b;
	a = a;
}