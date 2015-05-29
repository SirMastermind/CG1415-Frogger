/*
 * LightSource.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist175624
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_
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
#include "Vector4.h"


class LightSource {
    
	protected:
		Vector4 *_ambient;
		Vector4 *_diffuse;
		Vector4 *_specular;
		Vector4 *_position;
		Vector4 *_direction;
		GLfloat _cut_off;
		GLfloat _exponent;
		GLenum _num;
		bool _state;

	public:
		LightSource();
		virtual ~LightSource();
		bool getState();
		void setState(bool state);
		GLenum getNum();
		void setPosition(Vector4 *position);
		void setDirection(Vector4 *direction);
		void setCutOff(double cut_off);
		void setExponent(double exponent);
		void setAmbient(Vector4 *ambient);
		void setDiffuse(Vector4 *diffuse);
		void setSpecular(Vector4 *specular);
		virtual void shine() = 0;
};

#endif /* LIGHTSOURCE_H_ */
