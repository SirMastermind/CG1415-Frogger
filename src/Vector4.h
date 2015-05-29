//
//  Vector4.h
//  CG_labs
//
//  Created by Tomás Alves on 03/10/14.
//
//

#ifndef __CG_labs__Vector4__
#define __CG_labs__Vector4__

#include <iostream>
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
#include "Vector3.h"
class Vector4: public Vector3 {
private:
    double _w;
public:
    Vector4();
    Vector4(double in_x, double in_y, double in_z, double in_w);
    ~Vector4();
    double getW();
    void set(double in_x, double in_y, double in_z, double in_w);
    Vector4 operator=(const Vector4 & in_vec);
    Vector4 operator*(double in_num);
    Vector4 operator+(const Vector4 & in_vec);
    Vector4 operator-(const Vector4 & in_vec);
};
#endif /* defined(__CG_labs__Vector4__) */