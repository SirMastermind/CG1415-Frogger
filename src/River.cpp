/*
 * River.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */
#include <stdio.h>
#include <iostream>
#include "River.h"
#include "Texture.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

River::River() {
}

River::~River() {
}


void River::draw(Texture* texture) {
	float x, y, z=0, u = 0, v = 0, u_plus = 1/440, v_plus = 1/140;

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture->gettextureID());
    
	glPushMatrix();
	
		glTranslatef (0, 5, 0);
    		glColor3f(0.3f, 0.3f, 1.f);
        const GLfloat blue[4] = { .3f, .3f, 1.f, 1.f };
        glMaterialfv( GL_FRONT, GL_DIFFUSE, blue );
        const GLfloat white[4] = { 0.5f, 0.5f, 0.5f, 1.f };
        glMaterialfv( GL_FRONT, GL_SPECULAR, white );
        glMaterialf( GL_FRONT, GL_SHININESS, 20.f );

		glBegin(GL_QUADS);
		    for(x=-11, u = (x+11)/22; x < 11; x += 0.05, u = (x+11)/22){
			    for(y=-3.5, v = (y+3.5)/7; y < 3.5; y += 0.05, v = (y+3.5)/7){
                    glNormal3f(0.0, 0.0, 1.0);
                    glTexCoord2f(u, v + v_plus);
                    glVertex3f(x, y+0.05, z);
                    glTexCoord2f(u, v);
				    glVertex3f(x, y ,z);
                    glTexCoord2f(u + u_plus,v);
                    glVertex3f(x+0.05, y, z);
                    glTexCoord2f(u + u_plus,v + v_plus);
				    glVertex3f(x+0.05, y+0.05, z);
			    }
		    }
		glEnd();
    glFlush();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
