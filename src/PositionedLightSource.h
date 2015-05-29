

#ifndef POSITIONEDLIGHTSOURCE_H_
#define POSITIONEDLIGHTSOURCE_H_
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

class PositionedLightSource : public LightSource {
	public:
		PositionedLightSource(GLenum number);
		~PositionedLightSource();
		void shine();
		void drawLightPost();
		void drawLampSphereEmission(double r, double g, double b);
};

#endif 
