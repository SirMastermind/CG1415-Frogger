/*
 * Car.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef CAR_H_
#define CAR_H_
#include "DynamicObject.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <iostream>

void drawTop();
void drawTire();
void drawBottom();

class Car: public DynamicObject {
	public:
		Car(Vector3* position);
		~Car();
		void draw();
        float* boxLimits();
};

#endif /* CAR_H_ */
