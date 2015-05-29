//
//  Texture.h
//  Proj_CG
//
//  Created by Tomás Alves on 11/11/14.
//  Copyright (c) 2014 Tomás Alves. All rights reserved.
//

#ifndef __Proj_CG__Texture__
#define __Proj_CG__Texture__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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

using namespace std;

class Texture {
    unsigned int textureID;
public:
    Texture(void* data, int w, int h, int format);
    static Texture* loadBMP(const char* filename);
    unsigned int gettextureID();
};

#endif /* defined(__Proj_CG__Texture__) */
