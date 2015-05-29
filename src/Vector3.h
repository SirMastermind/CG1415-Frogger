/*
 * Vector3.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <stdio.h>
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

class Vector3 {
	protected:
		double _x;
		double _y;
		double _z;
	public:
		Vector3();
		Vector3(double x, double y, double z);
		~Vector3();
		double getX() const;
		double getY() const;
		double getZ() const;
		void setX(double x);
		void setY(double x);
		void setZ(double x);
		
		void set(double x, double y, double z);
		Vector3 operator=(const Vector3 &vec);
		Vector3 operator*(double num);
		Vector3 operator+(const Vector3 &vec);
		Vector3 operator-(const Vector3 &vec);
		void print();
};

#endif /* VECTOR3_H_ */