#include <iostream>
#include "Message.h"
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

Message::Message() {
}

Message::~Message() {
}

void Message::draw(Texture* texture){
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texture->gettextureID());
    
	glColor3f(1.0, 1.0, 0.5);
    const GLfloat grey[4] = {.3, .3, .3, 1.f };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, grey );
    const GLfloat white[4] = { 0.508273f, 0.508273f, 0.508273f, 1.f };
    glMaterialfv( GL_FRONT, GL_SPECULAR, white );
    glMaterialf( GL_FRONT, GL_SHININESS, 0.2f * 128 );
	glPushMatrix();
		glBegin(GL_QUADS);
				glNormal3f(0.0, 0.0, 1.0);
                glTexCoord2f(0,1);
				glVertex3f(-4,4, 4);
                glTexCoord2f(0,0);
				glVertex3f(-4, -4,4);
                glTexCoord2f(1,0);
				glVertex3f(4, -4, 4);
                glTexCoord2f(1,1);
				glVertex3f(4, 4, 4);
    glEnd();
    glFlush();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}
