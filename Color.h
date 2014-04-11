#ifndef COLOR_H
#define COLOR_H


class Color{
private:
	double red, green, blue, a;

public:
	Color();

	Color(double r, double g, double b, double a);

	double getColorRed(){ return red; }

	double getColorGreen(){ return green; }

	double getColorBlue(){ return blue; }

	double getColorA(){ return a; }

	void setColor(double r, double g, double b, double a);


};
#endif