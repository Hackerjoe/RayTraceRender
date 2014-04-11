#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "Object.h"
#include "Vec.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"
using namespace std;



struct RGBType
{
	double r;
	double g;
	double b;
};

int currentPixel;


void saveBMP(const char *filename, int w, int h, int dpi, RGBType *data)
{
	FILE *f;
	int k = w*h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);
	int ppm = dpi*m;

	unsigned char bmpfileheader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
	unsigned char bmpinfoheader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[ 4] = (unsigned char)(w);
	bmpinfoheader[ 5] = (unsigned char)(w>>8);
	bmpinfoheader[ 6] = (unsigned char)(w>>16);
	bmpinfoheader[ 7] = (unsigned char)(w>>24);

	bmpinfoheader[ 8] = (unsigned char)(h);
	bmpinfoheader[ 9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);

	f = fopen(filename, "wb");
	
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int i = 0; i < k; i++)
	{
		RGBType rgb = data[i];

		double red =   (data[i].r) * 255;
		double green = (data[i].g) * 255;
		double blue =  (data[i].b) * 255;

		unsigned char color[3] = { (int)floor(blue), (int)floor(green), (int)floor(red) };
		fwrite(color, 1, 3, f);


	}
	fclose(f);
}

int ClosestObjectIndex(vector<double> objectIntersections)
{
	int indexOfMinValue;

	if (objectIntersections.size() == 0)
	{
		return -1;
	}
	else if (objectIntersections.size() ==1)
	{
		if (objectIntersections.at(0) > 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		double max = 0;
		for (int i = 0; i < objectIntersections.size(); i++)
		{
			if (max < objectIntersections.at(i))
			{
				max = objectIntersections.at(i);
			}
		}

		if (max > 0)
		{
			for (int index = 0; index < objectIntersections.size(); index++)
			{
				if (objectIntersections.at(index) > 0 && objectIntersections.at(index) <= max)
				{
					max = objectIntersections.at(index);
					indexOfMinValue = index;
				}
			}
			return indexOfMinValue;
		} else 
		{
			return -1;
		}

		
	}
	

}

int main(int argc, char *agrv[])
{
	cout << "rendering \n";
	
	
	int dpi = 72;
	int width = 640;
	int height = 480;
	double aspectRatio = (double)width / (double)height;
	int n = width*height;

	double xamnt, yamnt;

	RGBType *pixels = new RGBType[n];

	Vec x(1, 0, 0);
	Vec y(0, 1, 0);
	Vec z(0, 0, 1);

	Vec CameraPosition(3, 1.5, -4);
	Vec lookAt(0, 0, 0);
	Vec diffBtw(CameraPosition.getVecX() - lookAt.getVecX(), CameraPosition.getVecY() - lookAt.getVecY(), CameraPosition.getVecZ() - lookAt.getVecZ());
	Vec cameraDir = diffBtw.negative().normalize();
	Vec cameraRig = y.crossProduct(cameraDir).normalize();
	Vec camDow = cameraRig.crossProduct(cameraDir);

	Camera SceneCamera(CameraPosition, cameraDir, cameraRig, camDow);

	Color whiteLight(1.0, 1.0, 1.0, 0);
	Color green(0.5, 1.0, 0.5, 0.3);
	Color maroonUDig(0.5, 0.25, 0.25, 0);
	Color gray(0.5, 0.5, 0.5, 0);
	Color black(0, 0, 0, 0);

	Vec LightPos(-7, 10, -10);
	Light myLight(LightPos, whiteLight);

	Sphere mySphere1(Vec(0, 0, 0), 1, green);
	Plane myPlane1(y, -1, maroonUDig);
	vector<Object*> sceneObjects;
	sceneObjects.push_back(dynamic_cast<Object*>(&mySphere1));
	sceneObjects.push_back(dynamic_cast<Object*>(&myPlane1));

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			currentPixel = y*width + x;

			if (width > height)
			{
				xamnt = ((x + 0.5) / width)*aspectRatio - (((width - height) / (double)height / 2));
				yamnt = ((height - y) + 0.5) / height;
			}
			else if (height > width)
			{
				xamnt=(x + 0.5) / width;
				yamnt = (((height - y) + 0.5) / height) / aspectRatio - (((height - width) / (double)width) / 2);
			}
			else{
				xamnt = (x + 0.5) / width;
				yamnt = ((height - y) + 0.5) / height;
			}
			Vec camRayOrigin = SceneCamera.getCameraPos();
			Vec camRayDirection = cameraDir.addVec(cameraRig.MultiplyVec(xamnt - 0.5).addVec(camDow.MultiplyVec(yamnt - 0.5))).normalize();

			Ray camRay(camRayOrigin, camRayDirection);

			vector<double> intersections;

			for (int index = 0; index < sceneObjects.size(); index++)
			{
				intersections.push_back(sceneObjects.at(index)->findIntersection(camRay));
			}

			int indexOfClosestObject = ClosestObjectIndex(intersections);
			cout << indexOfClosestObject;
			if (indexOfClosestObject == -1)
			{
				pixels[currentPixel].r = 0;
				pixels[currentPixel].g = 0;
				pixels[currentPixel].b = 0;
			}
			else
			{
				Color currentColor = sceneObjects.at(indexOfClosestObject)->getColor();
				pixels[currentPixel].r = currentColor.getColorRed();
				pixels[currentPixel].g = currentColor.getColorGreen();
				pixels[currentPixel].b = currentColor.getColorBlue();
			}

		}
	}

	saveBMP("scene.bmp", width, height, dpi, pixels);
	return 0;
}