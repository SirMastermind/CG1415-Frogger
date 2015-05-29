/*
 * StaticObject.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef STATICOBJECT_H_
#define STATICOBJECT_H_
#include "GameObject.h"
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
class StaticObject: public GameObject {
	public:
		StaticObject();
		~StaticObject();
        virtual void draw(Texture* texture){};
};

#endif /* STATICOBJECT_H_ */
