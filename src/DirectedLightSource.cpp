/*
 * DirectedLightSource.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist175624
 */

#include "DirectedLightSource.h"
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

#include <list>

DirectedLightSource::DirectedLightSource(GLenum number) {
	_num = number;
}

DirectedLightSource::~DirectedLightSource() {
}



void DirectedLightSource::shine(){
		GLfloat ambient[] = {static_cast<GLfloat>(_ambient->getX()), static_cast<GLfloat>(_ambient->getY()), static_cast<GLfloat>(_ambient->getZ()), static_cast<GLfloat>(_ambient->getW())};
		GLfloat diffuse[] = {static_cast<GLfloat>(_diffuse->getX()),static_cast<GLfloat>(_diffuse->getY()), static_cast<GLfloat>(_diffuse->getZ()), static_cast<GLfloat>(_diffuse->getW())};
		GLfloat specular[] = {static_cast<GLfloat>(_specular->getX()),static_cast<GLfloat>(_specular->getY()), static_cast<GLfloat>(_specular->getZ()), static_cast<GLfloat>(_specular->getW())};
		GLfloat direction[] = {static_cast<GLfloat>(_direction->getX()), static_cast<GLfloat>(_direction->getY()), static_cast<GLfloat>(_direction->getZ()), static_cast<GLfloat>(_direction->getW())};
		
		glLightfv(_num, GL_AMBIENT, ambient );		//sets light that comes from all directions to "day mode"
		glLightfv(_num, GL_DIFFUSE, diffuse );		//diffuse reflection reflects light in all directions
		glLightfv(_num, GL_SPECULAR, specular);		//sets the specular color (white)
		glLightfv(_num, GL_POSITION, direction);	//the direction
}