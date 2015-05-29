//
//  Vector4.cpp
//  CG_labs
//
//  Created by Tomás Alves on 03/10/14.
//
//

#include "Vector4.h"
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

Vector4::Vector4() :Vector3(){
	_w=0.0;
}

Vector4::Vector4(double in_x, double in_y, double in_z, double in_w) :Vector3(in_x, in_y, in_z){
	_w=in_w;
}

Vector4::~Vector4(){
}

void Vector4::set(double in_x, double in_y, double in_z, double in_w){
	Vector3::set(in_x, in_y, in_z);
	_w=in_w;
}

double Vector4::getW(){
	return _w;
}