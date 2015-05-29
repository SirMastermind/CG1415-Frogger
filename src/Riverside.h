/*
 * Riverside.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef RIVERSIDE_H_
#define RIVERSIDE_H_
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

class Riverside : public StaticObject {
	public:
		Riverside();
		~Riverside();
		void draw(Texture* texture);
};

#endif /* RIVERSIDE_H_ */