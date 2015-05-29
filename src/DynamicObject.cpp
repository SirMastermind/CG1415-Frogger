/*
 * DynamicObject.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#include "DynamicObject.h"
#include "Entity.h"
#include "Vector3.h"
#include "stdio.h"
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

DynamicObject::DynamicObject() {
	_time=0;

}

DynamicObject::~DynamicObject() {
}

void DynamicObject::setTime(float time){
	_time=time;
}

float DynamicObject::getTime(){
	return _time;
}

void DynamicObject::setSpeed(double x, double y, double z){
	_speed.set(x, y, z);
}



void DynamicObject::update(double delta_t){
		if(getTime()>0) return;
		Vector3 *position=Entity::getPosition();

		Entity::setPosition(position->getX()+delta_t*_speed.getX(), position->getY()+delta_t*_speed.getY(), position->getZ()+delta_t*_speed.getZ());
}

Vector3 DynamicObject::getSpeed(){
	return _speed;
}

Vector3 DynamicObject::getDirection(){
	return _direction;
}

void DynamicObject::setDirection(float x, float y, float z){
	_direction.set(x,y,z);
}