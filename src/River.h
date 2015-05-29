/*
 * River.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef RIVER_H_
#define RIVER_H_
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
class River : public StaticObject {
    GLuint texture;
	public:
		River();
		~River();
		void draw(Texture* texture);
    GLuint loadTexture(std::string filename);
};

#endif /* RIVER_H_ */
