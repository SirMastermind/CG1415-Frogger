/*
 * Car.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#include "Car.h"
#include "auxiliares.h"
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
#include <stdio.h>

Car::Car(Vector3* position) {
	_position = position;
}

Car::~Car() {
}

float* Car::boxLimits() {
    float *limits = new float[4];
    // xmin
    limits[0] = getPosition()->getX() - 1.35;
    // xmax
    limits[1] = getPosition()->getX() + 1.35;
    // ymin
    limits[2] = getPosition()->getY() - 0.65;
    // ymax
    limits[3] = getPosition()->getY() + 0.65;
    return limits;
}
 
void Car::draw(){
	glPushMatrix();
	glTranslatef (getPosition()->getX(), getPosition()->getY(), getPosition()->getZ());
	glScalef(0.75, 0.75, 0.75);
	
	// Car's bottom
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.2);
		glColor3f( 0.4f, 0.4f, 0.4f );
        const GLfloat chrome[4] = {0.4f, 0.4f, 0.4f, 1.f };
        glMaterialfv( GL_FRONT, GL_DIFFUSE, chrome );
        const GLfloat specs_chrome[4] = { 0.774597, 0.774597, 0.774597, 1.f };
        glMaterialfv( GL_FRONT, GL_SPECULAR, specs_chrome );
        glMaterialf( GL_FRONT, GL_SHININESS, .6f * 128 );
		glScalef (1.8, 0.7, 0.4);
		drawBottom();
	glPopMatrix();
	
	// Car's cabin
	glPushMatrix();
		glColor3f( 0.4f, 0.4f, 0.4f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, chrome );
        glMaterialfv( GL_FRONT, GL_SPECULAR, specs_chrome );
        glMaterialf( GL_FRONT, GL_SHININESS, .4f * 128 );
		glScalef (0.6, 0.653439, 0.587);
		glTranslatef (0.0, 0.0, 1.0);  
		drawTop();
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.3);
    
	// Left back tire
	glPushMatrix();
	glTranslatef (-1.0, 0.875, 0.0);
	drawTire();
	glPopMatrix();
	
	// Right front tire
	glPushMatrix();
	glTranslatef (1.0, -1.0, 0.0);
	drawTire();
	glPopMatrix();
	
	// Right back tire
	glPushMatrix();
	glTranslatef (-1.0, -1.0, 0.0);
	drawTire();
	glPopMatrix();
	
	// Left front tire
	glPushMatrix();
	glTranslatef (1.0, 0.875, 0.0);
	drawTire();
	glPopMatrix();
	
	glPopMatrix();
	
	glPopMatrix();
}


void drawTop(){
	float y;
		glColor3f(0.3f, 0.3f, 1.f);
    const GLfloat turquoise[4] = { .3f, .3f, 1.f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, turquoise );
    const GLfloat specs_turquoise[4] = { 0.297254f, 0.30829f, 0.306678f, 1.f };
    glMaterialfv( GL_FRONT, GL_SPECULAR, specs_turquoise );
    glMaterialf( GL_FRONT, GL_SHININESS, .1f * 128 );
	for(y=-1.0; y<=1.0; y+=2.0){
		glBegin(GL_TRIANGLES);			
			Vector3* normal = calculateNormal(new Vector3 (-1, y, 0), new Vector3 ( 0.0, y, 0.0), new Vector3(-0.5, y, 0.75));
			Normal(normal);
			glVertex3f(-1.0, y, 0);
			glVertex3f(0.0, y, 0);
			glVertex3f(-0.5, y, 0.75);
			normal = calculateNormal(new Vector3 (0.0,y, 0), new Vector3 (1, y, 0.0), new Vector3(0.5, y, 0.75));
			Normal(normal);
			glVertex3f(0.0, y, 0);
			glVertex3f(1, y, 0);
			glVertex3f(0.5, y, 0.75);
			normal = calculateNormal(new Vector3 (0.0,y, 0), new Vector3 (0.5, y, 0.75), new Vector3(-0.5, y, 0.75));
			Normal(normal);
			glVertex3f(0.0, y, 0);
			glVertex3f(0.5, y, 0.75);
			glVertex3f(-0.5, y, 0.75);
		glEnd();  
	}
	glPushMatrix();
	glColor3f(0.61424f, 0.04136f, 0.04136f);
    const GLfloat ruby[4] = {0.61424f, 0.04136f, 0.04136f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, ruby );
    const GLfloat specs_ruby[4] = { 0.727811, 0.626959, 0.626959, 1.f };
    glMaterialfv( GL_FRONT, GL_SPECULAR, specs_ruby );
    glMaterialf( GL_FRONT, GL_SHININESS, .6f * 128 );
	glBegin(GL_QUADS);
		
		Vector3* normal = calculateNormal(new Vector3 (-1, -1, 0), new Vector3 ( -1/2, -1, 0.75), new Vector3(-1, 1, 0));
		Normal(normal);
		glNormal3f(1,0,1 );
		glVertex3f(-1.,-1, 0); 
		normal = calculateNormal(new Vector3( -1/2, -1, 0.75), new Vector3(-1.,-1, 0) , new Vector3(-1/2, -1.0, 0.75));
		Normal(normal);
		glVertex3f(-0.5, -1.0, 0.75);
		normal = calculateNormal(new Vector3 (-1/2, 1, 0.75), new Vector3 ( -1/2, -1, 0.75), new Vector3(-1, 1, 0));
		Normal(normal);
		glVertex3f(-0.5, 1.0, 0.75);
		normal = calculateNormal(new Vector3 (-1, 1, 0), new Vector3 ( -1/2, 1, 0.75), new Vector3(-1, -1, 0));
		Normal(normal);
		glVertex3f(-1., 1.0, 0);

	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.07568f, 0.61424f, 0.07568f);
    const GLfloat emerald[4] = {0.07568f, 0.61424f, 0.07568f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, emerald );
    const GLfloat specs_emerald[4] = { 0.633, 0.727811, 0.633, 1.f };
    glMaterialfv( GL_FRONT, GL_SPECULAR, specs_emerald );
    glMaterialf( GL_FRONT, GL_SHININESS, .6f * 128 );
	glBegin(GL_QUADS);
			normal = calculateNormal(new Vector3( 1, 1, 0), new Vector3(1/2, 1, 0.75) , new Vector3(1, -1.0, 0));
			Normal(normal);
			glVertex3f(1., 1.0, 0);
			normal = calculateNormal(new Vector3( 1/2, 1, 0.75), new Vector3(1.,1, 0) , new Vector3(1/2, -1.0, 0.75));
			Normal(normal);
			glVertex3f(0.5, 1.0, 0.75);
			normal = calculateNormal(new Vector3( 1/2, -1, 0.75), new Vector3(1/2, 1, 0.75) , new Vector3(1.,-1, 0));
			Normal(normal);
			glVertex3f(0.5, -1.0, 0.75);
			normal = calculateNormal(new Vector3 (1, 1, 0), new Vector3 ( 1/2, 1, 0.75), new Vector3(1, 1, 0));
			Normal(normal);
			glVertex3f(1.,-1, 0); 
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 1.f);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, turquoise );
    glMaterialfv( GL_FRONT, GL_SPECULAR, specs_turquoise );
    glMaterialf( GL_FRONT, GL_SHININESS, .1f * 128 );
	glBegin(GL_QUADS);
		glNormal3f(0, 0 , 1.0);
		glVertex3f(-0.5, -1.0, 0.75);
		glVertex3f(0.5, -1.0, 0.75);
		glVertex3f(0.5, 1.0, 0.75);
		glVertex3f(-0.5, 1.0, 0.75);
	glEnd();
	glPopMatrix();
}

void drawTire(){
	glColor3f(0.1, 0.1, 0.1);
    const GLfloat black_rubber[4] = {.1f, .1f, .1f, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, black_rubber );
    const GLfloat specs_black_rubber[4] = { .4f, .4f, .4f, 1.f };
    glMaterialfv( GL_FRONT, GL_SPECULAR, specs_black_rubber );
    glMaterialf( GL_FRONT, GL_SHININESS, .078125f * 128 );
	glBegin(GL_TRIANGLES);
		glNormal3f(0.0, -1.0, 0.0);
		// Up half
		glVertex3f(-0.25f, 0, 0.0f);
		glVertex3f(0.0f, 0, 0.0f);
		glVertex3f(-0.125f,0,.2165f);
		
		glVertex3f(	0.0f, 0, 0.0f);
		glVertex3f(0.125f, 0,.2165f);
		glVertex3f(-0.125f, 0,.2165f);
		
		glVertex3f(0,0,0);
		glVertex3f(0.25,0,0);
		glVertex3f(0.125,0,0.2165);

		// Down half
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-0.125f,0,-.2165f);
		glVertex3f(0.0f, 0, 0.0f);
		glVertex3f(-0.25f, 0.0f, 0.0f);

		glVertex3f(-0.125f, 0.0f,-.2165f);
		glVertex3f(0.125f, 0.0f,-.2165f);
		glVertex3f(	0.0f, 0.0f, 0.0f);
		
		glVertex3f(0.125,0,-0.2165);
		glVertex3f(0.25,0,0);
		glVertex3f(0,0,0);
		
		
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(-1, 0,1);
		glVertex3f(-.125,0,.2165);
		glNormal3f(1, 0,1);
		glVertex3f(.125,0,.2165);
		glNormal3f(1, 1,1);
		glVertex3f(.125,.125,.2165);
		glNormal3f(-1, 1,1);
		glVertex3f(-.125,.125,.2165);

		glNormal3f(-1, 0, 0);
		glVertex3f(-.25,0,0);
		glNormal3f(-1, 0, 1);
		glVertex3f(-.125,0,.2165);
		glNormal3f(-1, 1, 1);
		glVertex3f(-.125,.125,.2165);
		glNormal3f(-1, 1, 0);
		glVertex3f(-.25,.125,0);

		glNormal3f(1, 0, 0);
		glVertex3f(.25,0,0);
		glNormal3f(1, 1, 0);
		glVertex3f(.25,.125,0);
		glNormal3f(1, 1, 1);
		glVertex3f(.125,.125,.2165);
		glNormal3f(1, 0, 1);
		glVertex3f(.125,0,.2165);
		
		glNormal3f(-1, 0, -1);
		glVertex3f(-.125,0,-.2165);
		glNormal3f(-1, 0, 0);
		glVertex3f(-.25,0,0);
		glNormal3f(-1, 1, 0);
		glVertex3f(-.25,0.125,0);
		glNormal3f(-1, 1, -1);
		glVertex3f(-.125,.125,-.2165);
		
		glNormal3f(-1, 0, -1);
		glVertex3f(-.125,0,-.2165);
		glNormal3f(1, 0, -1);
		glVertex3f(.125,0,-.2165);
		glNormal3f(1, 1, -1);
		glVertex3f(.125,.125,-.2165);
		glNormal3f(1, 1, -1);
		glVertex3f(-.125,.125,-.2165);

		glNormal3f(1, 0, -1);
		glVertex3f(.125,0,-.2165);
		glNormal3f(1, 1, -1);
		glVertex3f(.125,.125,-.2165);
		glNormal3f(1, 1, 0);
		glVertex3f(.25,.125,0);
		glNormal3f(1, 0, 0);
		glVertex3f(.25,0,0);
	glEnd();
}

void drawBottom(){
	glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads
			
		  // Front face (y = 1.0f)
		  // Define vertices in counter-clockwise (CCW) order with normal pointing out
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f( 1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f,  1.0f);
			glVertex3f( 1.0f, 1.0f,  1.0f);
	 
		  // Back face (y = -1.0f)
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f( 1.0f, -1.0f,  1.0f);
			glVertex3f(-1.0f, -1.0f,  1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f( 1.0f, -1.0f, -1.0f);
	 
		  // Top face  (z = 1.0f)
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f( 1.0f,  1.0f, 1.0f);
			glVertex3f(-1.0f,  1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f( 1.0f, -1.0f, 1.0f);
	 
		  // Bottom face (z = -1.0f)
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f( 1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f,  1.0f, -1.0f);
			glVertex3f( 1.0f,  1.0f, -1.0f);
	 
		  // Left face (x = -1.0f)
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-1.0f,  1.0f,  1.0f);
			glVertex3f(-1.0f,  1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f,  1.0f);
	 
		  // Right face (x = 1.0f) 
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(1.0f,  1.0f, -1.0f);
			glVertex3f(1.0f,  1.0f,  1.0f);
			glVertex3f(1.0f, -1.0f,  1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd(); 
}