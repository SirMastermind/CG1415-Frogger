/*
 * Riverside.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */
#include <iostream>
#include "Riverside.h"
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

Riverside::Riverside() {
}

Riverside::~Riverside() {
}

void Riverside::draw(Texture* texture){
    float x, y, z=0.0005;
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture->gettextureID());
    
	glPushMatrix();
        glTranslatef (0, 8.3, 0.0005);
        glColor3f(0.07568f, 0.61424f,0.07568f);
        const GLfloat emerald[4] = {0.07568f, 0.61424f, 0.07568f, 1.f };
        glMaterialfv( GL_FRONT, GL_DIFFUSE, emerald );
        const GLfloat specs_emerald[4] = { 0.633, 0.727811, 0.633, 1.f };
        glMaterialfv( GL_FRONT, GL_SPECULAR, specs_emerald );
        glMaterialf( GL_FRONT, GL_SHININESS, .6f * 128 );
        glBegin(GL_QUADS);
        for(x=-11; x<11;x+=1){
            for(y = -0.5; y < 0.5; y+=1){
                glNormal3f(0.0, 0.0, 1.0);
                glTexCoord2f(0,1);
                glVertex3f(x, y+1, z);
                glTexCoord2f(0,0);
                glVertex3f(x, y ,z);
                glTexCoord2f(1,0);
                glVertex3f(x+1, y, z);
                glTexCoord2f(1,1);
                glVertex3f(x+1, y+1, z);
            }
        }
        glEnd();
        glFlush();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}