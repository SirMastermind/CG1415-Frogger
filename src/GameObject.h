/*
 * GameObject.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist175624
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "Entity.h"
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
class GameObject: public Entity {

	public:
		GameObject();
		~GameObject();
    
		virtual void update(double delta_t){};
};

#endif /* GAMEOBJECT_H_ */
