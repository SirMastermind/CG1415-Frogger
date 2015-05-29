/*
 * Roadside.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */
#include <iostream>
#include "Roadside.h"
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

Roadside::Roadside() {
}

Roadside::~Roadside() {
}

void Roadside::draw(Texture* texture){
    float x, y, z=0;
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture->gettextureID());
    
    glPushMatrix();
        glTranslatef (0, 0.5, 0);
		glColor3f(1.f, 0.829f, 0.829f );
        const GLfloat pearl[4] = {1.f, 0.829f, 0.829f, 1.f };
        glMaterialfv( GL_FRONT, GL_DIFFUSE, pearl );
        const GLfloat specs_pearl[4] = { 0.296648f, 0.296648f, 0.296648f, 1.f };
        glMaterialfv( GL_FRONT, GL_SPECULAR, specs_pearl );
        glMaterialf( GL_FRONT, GL_SHININESS, 0.088f * 128 );
        glBegin(GL_QUADS);
        for(x=-11; x<11;x+=1){
            for(y=-1; y < 1; y+=1){
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
        glPushMatrix();
            glTranslatef (0, -7.4, 0);
            glMaterialfv( GL_FRONT, GL_DIFFUSE, pearl );
            glMaterialfv( GL_FRONT, GL_SPECULAR, specs_pearl );
            glMaterialf( GL_FRONT, GL_SHININESS, 0.088f * 128 );
            glBegin(GL_QUADS);
            for(x=-11; x<11;x+=1){
                for(y=-1; y < 1; y+=1){
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
        glPopMatrix();
    glFlush();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
