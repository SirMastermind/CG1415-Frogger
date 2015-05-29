/*
 * Vida.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#include <iostream>
#include <stdio.h>
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
#include "Vida.h"
#include "Vector3.h"
#include "GameManager.h"
#include "Texture.h"

Vida::Vida(Vector3* position) {
	_position = position;
}

Vida::~Vida() {
}

void Vida::draw(int nrvida, Texture* texture_head, Texture* texture_eyes){
	glPushMatrix();
		
		glTranslatef (getPosition()->getX()+nrvida, getPosition()->getY(), getPosition()->getZ());
		glScalef(1.5, 1.5, 2.1);
		glRotatef(90, 1, 0,0);
    
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, texture_head->gettextureID());
	
		// Head
		glPushMatrix();
            glColor3f(45/255.0, 189/255.0, 58/255.0);
            const GLfloat green[4] = {45/255.0, 189/255.0, 58/255.0, 1.f };
            const GLfloat specs_green[4] = { 0.316228f, 0.316228f, 0.316228f, 1.f };
            glMaterialfv( GL_FRONT, GL_DIFFUSE, green );
            glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green );
            glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
            glTranslatef (0.0, 0.6, 0.0);
            glScalef(1.2, 1.0, 1.0);
            GLUquadricObj *quadric_head;
            quadric_head=gluNewQuadric();
            gluQuadricNormals(quadric_head, GLU_SMOOTH);
            gluQuadricTexture(quadric_head, GL_TRUE);
            gluSphere(quadric_head,.25,10,10);
            glFlush();
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
		
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glBindTexture(GL_TEXTURE_2D, texture_eyes->gettextureID());
		// Eyes
			// Left
			glPushMatrix();
                const GLfloat pearl[4] = {1.f, 0.829f, 0.829f, 1.f };
                glMaterialfv( GL_FRONT, GL_DIFFUSE, pearl );
                const GLfloat specs_pearl[4] = { 0.296648f, 0.296648f, 0.296648f, 1.f };
                glMaterialfv( GL_FRONT, GL_SPECULAR, specs_pearl );
                glMaterialf( GL_FRONT, GL_SHININESS, 0.088f * 128 );
				glColor3f(1.0f, 1.0f, 1.0f);
				glScalef(0.5, 0.5, 0.5);
				glTranslatef(-0.25, 0.25, 0.0);
                GLUquadricObj *quadric_left;
                quadric_left=gluNewQuadric();
                gluQuadricNormals(quadric_left, GLU_SMOOTH);
                gluQuadricTexture(quadric_left, GL_TRUE);
                gluSphere(quadric_left,.2,5,5);
			glPopMatrix();
    
			// Right
			glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
                glMaterialfv( GL_FRONT, GL_DIFFUSE, pearl );
                glMaterialfv( GL_FRONT, GL_SPECULAR, specs_pearl );
                glMaterialf( GL_FRONT, GL_SHININESS, 0.088f * 128 );
				glScalef(0.5, 0.5, 0.5);
				glTranslatef(0.25, 0.25, 0.0);
                GLUquadricObj *quadric_right;
                quadric_right=gluNewQuadric();
                gluQuadricNormals(quadric_right, GLU_SMOOTH);
                gluQuadricTexture(quadric_right, GL_TRUE);
                gluSphere(quadric_right,.2,5,5);
			glPopMatrix();
		glPopMatrix();
    glFlush();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
