/*
 * PositionedLightSource.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist175624
 */

#include "PositionedLightSource.h"
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

#include <list>

PositionedLightSource::PositionedLightSource(GLenum number) {
	_num = number;
}

PositionedLightSource::~PositionedLightSource() {
}



void PositionedLightSource::shine(){
		GLfloat ambient[] = {static_cast<GLfloat>(_ambient->getX()), static_cast<GLfloat>(_ambient->getY()), static_cast<GLfloat>(_ambient->getZ()), static_cast<GLfloat>(_ambient->getW())};
		GLfloat diffuse[] = {static_cast<GLfloat>(_diffuse->getX()),static_cast<GLfloat>(_diffuse->getY()), static_cast<GLfloat>(_diffuse->getZ()), static_cast<GLfloat>(_diffuse->getW())};
		GLfloat specular[] = {static_cast<GLfloat>(_specular->getX()),static_cast<GLfloat>(_specular->getY()), static_cast<GLfloat>(_specular->getZ()), static_cast<GLfloat>(_specular->getW())};
		GLfloat position[] = {static_cast<GLfloat>(_position->getX()),static_cast<GLfloat>(_position->getY()), static_cast<GLfloat>(_position->getZ()), static_cast<GLfloat>(_position->getW())};
		GLfloat direction[] = {static_cast<GLfloat>(_direction->getX()),static_cast<GLfloat>(_direction->getY()), static_cast<GLfloat>(_direction->getZ()), static_cast<GLfloat>(_direction->getW())};
		
		glLightfv(_num, GL_DIFFUSE, diffuse );		// Diffuse reflection reflects light in all directions
		glLightfv(_num, GL_SPECULAR, specular);		// Sets the specular color (white)
		glLightfv(_num, GL_POSITION, position);	// The position from which the ligh is shining
		glLightfv(_num, GL_SPOT_DIRECTION, direction);	// Direction where the light is pointing at
		glLightfv(_num, GL_SPOT_CUTOFF, &_cut_off); // 0~180º  intensity distribution of the light
		glLightfv(_num, GL_SPOT_EXPONENT, &_exponent); // 0~128  maximum spread angle of the light source
}


void PositionedLightSource::drawLightPost(){
		GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
		GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
		GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
		GLfloat mat_emission[] = {0.4, 0.4, 0.4, 1.0};
		GLfloat mat_shine = 100.0;
		
		glPushMatrix();
		
			glTranslatef(0.0, 0.0, -2.0);
			
			glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
			
			glColor3f( 133/255.0, 133/255.0, 133/255.0 );
			glTranslatef(_position->getX(), _position->getY(), _position->getZ() - 2.0 );
			
			glBegin(GL_POLYGON);
				GLUquadricObj *obj = gluNewQuadric();
				gluCylinder(obj, 0.1, 0.1, 2.0, 50, 50);
			glEnd();
		
		glPopMatrix();
		
		if(getState())
			drawLampSphereEmission(0.4, 0.4, 0.4);
		else
			drawLampSphereEmission(0.0, 0.0, 0.0);
}



void PositionedLightSource::drawLampSphereEmission(double r, double g, double b){
	 GLfloat mat_emission[] = {static_cast<GLfloat>(r), static_cast<GLfloat>(g), static_cast<GLfloat>(b), 1.0};
	 
	 glPushMatrix();
		glTranslatef(_position->getX(), _position->getY(), _position->getZ() - 2.0 );
		glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
		
		const GLfloat pearl[4] = {1.f, 0.829f, 0.829f, 1.f };
		glMaterialfv( GL_FRONT, GL_DIFFUSE, pearl );
		
		const GLfloat specs_pearl[4] = { 0.296648f, 0.296648f, 0.296648f, 1.f };
		glMaterialfv( GL_FRONT, GL_SPECULAR, specs_pearl );
		
		glMaterialf( GL_FRONT, GL_SHININESS, 0.088f * 128 );
    
        glColor3f(1.0f, 0.829f, 0.829f);
		glutSolidSphere(0.4, 10, 10);
		
		GLfloat mat_emission2[] = {0, 0, 0, 1.0};
		glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission2);
	 
	 glPopMatrix();
 }