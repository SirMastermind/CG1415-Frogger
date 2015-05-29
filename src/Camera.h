/*
 * Camera.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist175624
 */

#ifndef CAMERA_H_
#define CAMERA_H_
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
#include "Vector3.h"
#include "Entity.h"


class Camera: public Entity {

	protected:
			Vector3 _up;
			Vector3 _at;
			double _near;
			double _far;

	public:
		Camera(double dnear, double dfar);
		Camera();
		virtual ~Camera();
		
		virtual void computeProjectionMatrix() = 0;
		virtual void computeVisualizationMatrix(double eyeX, double eyeY, double eyeZ, double targetX, double targetY, double targetZ, double upX, double upY, double upZ) = 0;
};





#endif /* CAMERA_H_ */
