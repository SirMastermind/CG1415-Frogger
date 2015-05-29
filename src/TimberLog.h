/*
 * TimberLog.h
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#ifndef TIMBERLOG_H_
#define TIMBERLOG_H_
#include "DynamicObject.h"
#include "Texture.h"

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
class TimberLog : public DynamicObject {
	public:
		TimberLog(Vector3* position);
		~TimberLog();
		void draw(Texture* texture);
        int getType();
        float* boxLimits();
};

#endif /* TIMBERLOG_H_ */
