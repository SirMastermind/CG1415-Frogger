/*
 * Frog.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef FROG_H_
#define FROG_H_
#include "DynamicObject.h"
#include "Vector3.h"
#include "Texture.h"
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

class Frog  : public DynamicObject {
	private:
		Vector3* _direction;
		Vector3* _toRotate;
	public:
		Frog(Vector3* position);
		~Frog();
		void draw(Texture* texture);
		void rotate(Vector3* direction);
		void setToRotate(double x, double y, double z);
		void rotate();
		void setDirection(double x, double y, double z);
		Vector3* getDirection();
		float* boxLimits();
};

#endif /* FROG_H_ */
