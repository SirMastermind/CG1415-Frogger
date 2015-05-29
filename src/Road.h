/*
 * Road.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef ROAD_H_
#define ROAD_H_
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

class Road : public StaticObject {
	public:
		Road();
		~Road();
		void draw(Texture* tex);
};

#endif /* ROAD_H_ */
