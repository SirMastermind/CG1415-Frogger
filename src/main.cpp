#include <iostream>
#include <stdio.h>

#include "GameManager.h"
#include "Texture.h"
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

GameManager* game;

void reshape(GLsizei w, GLsizei h){
	game->reshape(w,h);
}
void display(){
	game->display();
}

void keyPressed(unsigned char key, int x, int y){
	game->keyPressed(key, x, y);
}

void keyUp(unsigned char key, int x, int y){
	game->keyUp(key, x, y);
}

void idle(){
	game->idle();
}

void aumentaVelocidade(int value){
	game->testSpeedIncrease();
	glutTimerFunc(10000, aumentaVelocidade, 0);
}
	


int main(int argc, char** argv){
	
	game = new GameManager();
	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DEPTH |GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Frogger 2014");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_SPOT_EXPONENT);
	glEnable(GL_SPOT_CUTOFF);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	game->init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(10000, aumentaVelocidade, 0);
	glutMainLoop();
	return 0;
}