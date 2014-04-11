#include "Camera.h"

Camera::Camera()
{
	cameraPos = Vec(0, 0, 0);
	cameraDir = Vec(0, 0, 1);
	cameraRight = Vec(0, 0, 0);
	cameraDown = Vec(0, 0, 0);
}

Camera::Camera(Vec position, Vec direction, Vec Right, Vec Down)
{
	cameraPos = position;
	cameraDir = direction;
	cameraRight = Right;
	cameraDown = Down;
}