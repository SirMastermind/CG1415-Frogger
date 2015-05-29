//
//  OrthogonalCamera.h
//  CG_labs
//
//  Created by Tomás Alves on 03/10/14.
//
//

#ifndef __CG_labs__OrthogonalCamera__
#define __CG_labs__OrthogonalCamera__

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


class OrthogonalCamera: public Camera {
	
	private:
		double _right;
		double _left;
		double _top;
		double _bottom;
		double _ratio; 
		double _aspect;
	public:
		OrthogonalCamera();
		
		~OrthogonalCamera();
		void update(double right, double left, double bottom, double top, double dnear, double dfar, double ratio, double aspect);
		void computeProjectionMatrix();
		void computeVisualizationMatrix(double eyeX, double eyeY, double eyeZ, double targetX, double targetY, double targetZ, double upX, double upY, double upZ);
};
#endif /* defined(__CG_labs__OrthogonalCamera__) */
