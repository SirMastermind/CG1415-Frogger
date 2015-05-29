/*
 * TimberLog.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist176231
 */

#include "TimberLog.h"
#include "DynamicObject.h"
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
TimberLog::TimberLog(Vector3* position){
    _position = position;
}

TimberLog::~TimberLog(){
}

float* TimberLog::boxLimits(){
    float *limits = new float[4];
    // xmin
    limits[0] = getPosition()->getX() - 1.5;
    //xmax
    limits[1] = getPosition()->getX() + 1.5;
    //ymin
    limits[2] = getPosition()->getY() - 0.75;
    //ymax
    limits[3] = getPosition()->getY() + 0.75;
    return limits;
}

void TimberLog::draw(Texture* texture){
    float z=.1;
    glPushMatrix();
    
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, texture->gettextureID());
    
        glTranslatef (getPosition()->getX(), getPosition()->getY(), getPosition()->getZ());
    
        glPushMatrix();
            glColor3f(0.714f, 0.4284f, 0.18144f);
            const GLfloat bronze[4] = {0.714f, 0.4284f, 0.18144f, 1.f };
            glMaterialfv( GL_FRONT, GL_DIFFUSE, bronze );
            const GLfloat specs[4] = { 0.393548f, 0.271906f, 0.166721f, 1.f };
            glMaterialfv( GL_FRONT, GL_SPECULAR, specs );
            glMaterialf( GL_FRONT, GL_SHININESS, .2f * 128 );

            glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, 1.0);
            glTexCoord2f(0,1);
            glVertex3f(-1.5, .65, z);
            glTexCoord2f(0,0);
            glVertex3f(-1.5, -.65,z);
            glTexCoord2f(1,0);
            glVertex3f(1.5, -.65, z);
            glTexCoord2f(1,1);
            glVertex3f(1.5, .65, z);
            glEnd();
    
        glPopMatrix();
    glFlush();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}