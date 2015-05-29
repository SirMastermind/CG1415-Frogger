

#ifndef DIRECTEDLIGHTSOURCE_H_
#define DIRECTEDLIGHTSOURCE_H_
#include "LightSource.h"
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

class DirectedLightSource : public LightSource {
	public:
		DirectedLightSource(GLenum number);
		~DirectedLightSource();
		void shine();
};

#endif 
