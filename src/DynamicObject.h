/*
 * DynamicObject.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef DYNAMICOBJECT_H_
#define DYNAMICOBJECT_H_
#include "Vector3.h"
#include "GameObject.h"
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

class DynamicObject : public GameObject{
	
	protected: 
		Vector3 _speed;
		float _time;
		Vector3 _direction;

	public:
		DynamicObject();
		~DynamicObject();
    virtual void draw(){};
		void update(double delta_t);
		void setSpeed(const Vector3 &speed);
		void setSpeed(double x, double y, double z);
		Vector3 getSpeed();
		void setTime(float time);
		float getTime();
        virtual float* boxLimits() = 0;
        Vector3 getDirection();
        void setDirection(float x, float y, float z);
};

#endif /* DYNAMICOBJECT_H_ */
