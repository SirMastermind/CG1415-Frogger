#ifndef MESSAGE_H_
#define MESSAGE_H_
#include "StaticObject.h"
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
class Message : public StaticObject {
	public:
		Message();
		~Message();
		void draw(Texture* texture);
};

#endif /* ROAD_H_ */
