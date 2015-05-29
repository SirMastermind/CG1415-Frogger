/*
 * Entity.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#include "Entity.h"
#include <iostream>
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

Entity::Entity() {
	_position = new Vector3();
}

Entity::~Entity() {
	delete _position;
}

Vector3* Entity::getPosition(){
	return _position;
}

Vector3* Entity::setPosition(double x, double y, double z){
	_position=new Vector3(x, y,z);
	return _position;
}

Vector3* Entity::setPosition(Vector3* position){
	_position=new Vector3(position->getX(), position->getY(), position->getZ());
	return _position;
}