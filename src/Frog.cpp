/*
 * Frog.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */
#include <iostream>
#include <stdio.h>
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
#include "Frog.h"
#include "Vector3.h"
#include "GameManager.h"

Frog::Frog(Vector3* position) {
	_position = position;
	_toRotate = new Vector3(0.0, 1.0, 0.0);
}

Frog::~Frog() {
}

float* Frog::boxLimits(){
    float *limits = new float[4];
    
    //Frog_Direction_South
    if(_toRotate->getY()==-1.0){
        // xmin
        limits[0] = getPosition()->getX() - 0.34;
        //xmax
        limits[1] = getPosition()->getX() + 0.34;
        //ymin
        limits[2] = getPosition()->getY() - 0.44;
        //ymax
        limits[3] = getPosition()->getY() + 0.40;
        return limits;
    }
    //Frog_Direction_West
    else if (_toRotate->getX()==1.0){
        // xmin
        limits[0] = getPosition()->getX() - 0.44;
        //xmax
        limits[1] = getPosition()->getX() + 0.40;
        //ymin
        limits[2] = getPosition()->getY() - 0.34;
        //ymax
        limits[3] = getPosition()->getY() + 0.34;
        return limits;
    }
    //Frog_Direction_East
    else if (_toRotate->getX()==-1.0){
        // xmin
        limits[0] = getPosition()->getX() - 0.40;
        //xmax
        limits[1] = getPosition()->getX() + 0.44;
        //ymin
        limits[2] = getPosition()->getY() - 0.34;
        //ymax
        limits[3] = getPosition()->getY() + 0.34;
        return limits;
    }
    //Frog_Direction_North
    else {
        // xmin
        limits[0] = getPosition()->getX() - 0.34;
        //xmax
        limits[1] = getPosition()->getX() + 0.34;
        //ymin
        limits[2] = getPosition()->getY() - 0.40;
        //ymax
        limits[3] = getPosition()->getY() + 0.44;
        return limits;
    }
}

void Frog::draw(Texture* texture){
	glPushMatrix();
		glTranslatef (getPosition()->getX(), getPosition()->getY(), getPosition()->getZ());
		glScalef(0.5,0.5, 0.7);
    
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, texture->gettextureID());
		rotate();
    
		// Body
		glPushMatrix();
			glColor3f(45/255.0, 189/255.0, 58/255.0);
            const GLfloat green2[4] = {45/255.0, 189/255.0, 58/255.0, 1.f };
            glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
            const GLfloat specs_green2[4] = { 0.316228f, 0.316228f, 0.316228f, 1.f };
            glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
            glMaterialf( GL_FRONT, GL_SHININESS, 0.2f * 128 );
			glTranslatef (0.0, 0.0, 0.0);
			glScalef(0.75, 1.0, 0.5);
            GLUquadricObj *quadric;
            quadric=gluNewQuadric();
            gluQuadricNormals(quadric, GLU_SMOOTH);
            gluQuadricTexture(quadric, GL_TRUE);
            gluSphere(quadric,.5,10,10);
		glPopMatrix();
		
		// Head
		glPushMatrix();
            glColor3f(45/255.0, 189/255.0, 58/255.0);
            glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
            glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
            glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
			glTranslatef (0.0, 0.6, 0.0);
			glScalef(1.2, 1.0, 1.0);
            GLUquadricObj *quadric2;
            quadric2=gluNewQuadric();
            gluQuadricNormals(quadric2, GLU_SMOOTH);
            gluQuadricTexture(quadric2, GL_TRUE);
            gluSphere(quadric2,.25,10,10);
            glFlush();
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
    
		// Eyes
			// Left
			glPushMatrix();
                const GLfloat pearl[4] = {1.f, 0.829f, 0.829f, 1.f };
                glMaterialfv( GL_FRONT, GL_DIFFUSE, pearl );
                const GLfloat specs_pearl[4] = { 0.296648f, 0.296648f, 0.296648f, 1.f };
                glMaterialfv( GL_FRONT, GL_SPECULAR, specs_pearl );
                glMaterialf( GL_FRONT, GL_SHININESS, 0.088f * 128 );
				glColor3f(1.0f, 0.829f, 0.829f);
				glScalef(0.5, 0.5, 0.5);
				glTranslatef(-0.25, 0.25, 0.0);
				glutSolidSphere(0.2, 5, 5);
			glPopMatrix();
    
			// Right
			glPushMatrix();
				glColor3f(1.0f, 0.829f, 0.829f);
                glMaterialfv( GL_FRONT, GL_DIFFUSE, pearl );
                glMaterialfv( GL_FRONT, GL_SPECULAR, specs_pearl );
                glMaterialf( GL_FRONT, GL_SHININESS, 0.088f * 128 );
				glScalef(0.5, 0.5, 0.5);
				glTranslatef(0.25, 0.25, 0.0);
				glutSolidSphere(0.2, 5, 5);
			glPopMatrix();
    
		glPopMatrix();
		
    // Right front leg
    glPushMatrix();
        glScalef(1.0,1.0, 0.25);
        glPushMatrix();
            glColor3f(45/255.0, 189/255.0, 58/255.0);
            glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
            glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
            glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
            glTranslatef(0.5, 0.25,0.0);
            glScalef(0.75, .25, 1.0);
            glutSolidCube(0.5);
    
            glPushMatrix();
                glColor3f(45/255.0, 189/255.0, 58/255.0);
                glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
                glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
                glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
				glTranslatef(+0.75*0.25, 1,0.0);
				glScalef(0.25, 4, 1.0);
				glutSolidCube(0.5);
            glPopMatrix();
    
        glPopMatrix();
    
    
    // Right back leg
    glPushMatrix();
        glColor3f(45/255.0, 189/255.0, 58/255.0);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
        glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
        glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
        glTranslatef(0.5, -0.25,0.0);
        glScalef(0.75, .25, 1.0);
        glutSolidCube(0.5);
    
        glPushMatrix();
            glColor3f(45/255.0, 189/255.0, 58/255.0);
            glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
            glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
            glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
            glTranslatef(0.75*0.25, -1,0.0);
            glScalef(0.25, 4, 1.0);
            glutSolidCube(0.5);
        glPopMatrix();
    
    glPopMatrix();
    
    // Left front leg
    glPushMatrix();
        glColor3f(45/255.0, 189/255.0, 58/255.0);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
        glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
        glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
        glTranslatef(-0.5, 0.25,0.0);
        glScalef(0.75, .25, 1.0);
        glutSolidCube(0.5);
    
        glPushMatrix();
            glColor3f(45/255.0, 189/255.0, 58/255.0);
            glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
            glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
            glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
            glTranslatef(-0.75*0.25, 1,0.0);
            glScalef(0.25, 4, 1.0);
            glutSolidCube(0.5);
        glPopMatrix();
    
    glPopMatrix();
    
    // Left back leg
    glPushMatrix();
        glColor3f(45/255.0, 189/255.0, 58/255.0);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
        glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
        glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
        glTranslatef(-0.5, -0.25,0.0);
        glScalef(0.75, .25, 1.0);
        glutSolidCube(0.5);
    
        glPushMatrix();
            glColor3f(45/255.0, 189/255.0, 58/255.0);
            glMaterialfv( GL_FRONT, GL_DIFFUSE, green2 );
            glMaterialfv( GL_FRONT, GL_SPECULAR, specs_green2 );
            glMaterialf( GL_FRONT, GL_SHININESS, .5f * 128 );
            glTranslatef(-0.75*0.25, -1,0.0);
            glScalef(0.25, 4, 1.0);
            glutSolidCube(0.5);
        glPopMatrix();
    glPopMatrix();
glPopMatrix();
glPopMatrix();
}

void Frog::rotate(){
				if(_toRotate->getY()==-1.0){
                    glRotatef(180, 0.0, 0.0, 1.0);
                } else if (_toRotate->getX()==-1.0){
                    glRotatef(90, 0.0, 0.0, 1.0);
                } else if (_toRotate->getX()==1.0){
                    glRotatef(-90, 0.0, 0.0, 1.0);
                }
}


void Frog::setToRotate(double x, double y, double z){
    _toRotate->set(x, y, z);
}

void Frog::setDirection(double x, double y, double z){
    _direction->set(x, y, z);
}

Vector3* Frog::getDirection(){
    return _toRotate;
}