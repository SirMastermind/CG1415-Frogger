/*
 * Road.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */
#include <iostream>
#include "Road.h"
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

Road::Road() {
}

Road::~Road() {
}

void Road::draw(Texture* texture){
	float x, y, z=0;

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture->gettextureID());
    
	glPushMatrix();
		glTranslatef (0, -3.25, 0.005);
		glColor3f(0.5f, 0.5f, 0.5f);
        const GLfloat grey[4] = {.5, .5, .5, 1.f };
        glMaterialfv( GL_FRONT, GL_DIFFUSE, grey );
        const GLfloat white[4] = { 0.508273f, 0.508273f, 0.508273f, 1.f };
        glMaterialfv( GL_FRONT, GL_SPECULAR, white );
        glMaterialf( GL_FRONT, GL_SHININESS, 0.2f * 128 );
		glBegin(GL_QUADS);
		for(x=-11; x<11 ; x += 2){
			for(y=-3; y<3; y+= 2){
				glNormal3f(0.0, 0.0, 1.0);
                glTexCoord2f(0,1);
                glVertex3f(x, y+2, z);
                glTexCoord2f(0,0);
                glVertex3f(x, y ,z);
                glTexCoord2f(1,0);
                glVertex3f(x+2, y, z);
                glTexCoord2f(1,1);
                glVertex3f(x+2, y+2, z);
			}
		}
		glEnd();
        glFlush();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef (-10.0, -2.2, 0.01);
		glScalef(0.5, 0.15, 0.0);
		GLfloat amb[]={0.0f,0.0f,0.0f,1.0f};
		GLfloat diff[]={0.71f,0.71f,0.71f,1.0f};
		GLfloat spec[]={0.8f,0.8f,0.8f,1.0f};
		GLfloat shine=8;
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
		
		for(int i = 0; i < 45; i += 5){
				glPushMatrix();
				glTranslatef (i, 0, 0.0);
				glBegin(GL_QUADS);
				for(x=-1; x<1;x+=1){
					for(y=-0.2; y<0.2; y+=0.4){
						glNormal3f(0.0, 0.0, 1.0);
						glVertex3f(x, y+0.4, z);
						glVertex3f(x, y,z);
						glVertex3f(x+1, y, z);
						glVertex3f(x+1, y+0.4, z);
					}
				}
				glEnd();
				glPopMatrix();
			}
	glPopMatrix();
	
	glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef (-10.0, -4.2, 0.01);
			glScalef(0.5, 0.1, 0.);
			for(int i = 0; i < 45; i += 5){
				glPushMatrix();
						glTranslatef (i, 0, 0.0);
						glBegin(GL_QUADS);
						for(x=-1; x<1;x+=1){
							for(y=-0.2; y<0.2; y+=0.4){
								glNormal3f(0.0, 0.0, 1.0);
								glVertex3f(x, y+0.4, z);
								glVertex3f(x, y,z);
								glVertex3f(x+1, y, z);
								glVertex3f(x+1, y+0.4, z);
							}
						}
						glEnd();
				glPopMatrix();
			}
	glPopMatrix();
}