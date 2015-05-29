//
//  PerspectiveCamera.h
//  CG_labs
//
//  Created by Tomás Alves on 03/10/14.
//
//

#ifndef __CG_labs__PerspectiveCamera__
#define __CG_labs__PerspectiveCamera__

#include <iostream>
#include "Camera.h"
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


class PerspectiveCamera: public Camera {
	private:
		double _fov;
		double _aspect;
		double _ratio;
	public:
		PerspectiveCamera();
		~PerspectiveCamera();
		void update(double fov, double ratio, double aspect, double cnear, double cfar);
		void computeProjectionMatrix();
		void computeVisualizationMatrix(double eyeX, double eyeY, double eyeZ, double targetX, double targetY, double targetZ, double upX, double upY, double upZ);
};
#endif /* defined(__CG_labs__PerspectiveCamera__) */
