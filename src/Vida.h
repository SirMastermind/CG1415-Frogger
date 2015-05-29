/*
 * Frog.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef VIDA_H_
#define VIDA_H_
#include "StaticObject.h"
#include "Texture.h"
#include "Vector3.h"
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

class Vida : public StaticObject {
	public:
		Vida(Vector3* position);
		~Vida();
		void draw(int nrvida, Texture* texture_head, Texture* texture_eyes);
		void rotate();
		float* boxLimits();
};

#endif /* VIDA_H_ */
