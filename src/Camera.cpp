/*
 * Camera.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist175624
 */
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
#include "Camera.h"

Camera::Camera(double dnear, double dfar) {
	_near=dnear;
	_far=dfar;
}

Camera::Camera(){
}

Camera::~Camera() {
}


void Camera::computeProjectionMatrix(){
}

void Camera::computeVisualizationMatrix(double eyeX, double eyeY, double eyeZ, double targetX, double targetY, double targetZ, double upX, double upY, double upZ){
}

