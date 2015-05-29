/*
 * Roadside.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef ROADSIDE_H_
#define ROADSIDE_H_
#include "StaticObject.h"
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
class Roadside: public StaticObject {
	public:
		Roadside();
		~Roadside();
		void draw(Texture* tex);
};

#endif /* ROADSIDE_H_ */
