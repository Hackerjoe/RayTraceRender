#ifndef CAMERA_H
#define CAMERA_H
#include <math.h>
#include "Vec.h"

class Camera{

	Vec cameraPos, cameraDir, cameraRight, cameraDown;

public:
	Camera();

	Camera(Vec position, Vec direction, Vec Right, Vec Down );

	Vec getCameraPos() { return cameraPos; }
	Vec getCameraDir() { return cameraDir; }
	Vec getCameraRight() { return cameraRight; }
	Vec getCameraDown() { return cameraDown; }


};
#endif