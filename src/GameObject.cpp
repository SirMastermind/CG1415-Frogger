/*
 * GameObject.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: ist175624
 */
#include <stdio.h>
#include <iostream>
#include "GameObject.h"
#include "Entity.h"
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

GameObject::GameObject() {
}

GameObject::~GameObject() {
}

