//
//  GameManager.h
//  CG_labs
//
//  Created by Tomás Alves on 03/10/14.
//
//

#ifndef __CG_labs__GameManager__
#define __CG_labs__GameManager__

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

#include <iostream>
#include <list>

#include "GameObject.h"
#include "DynamicObject.h"
#include "Frog.h"
#include "Camera.h"
#include "PerspectiveCamera.h"
#include "OrthogonalCamera.h"
#include "Vector3.h"
#include "LightSource.h"
#include "DirectedLightSource.h"
#include "StaticObject.h"
#include "PositionedLightSource.h"
#include "TimberLog.h"
#include "Message.h"
#include "Vida.h"


class GameManager {
	
	private:
		std::list <StaticObject*> _game_objects;
		GLfloat _tant, _tact, _delta;
		int _cameraLook, _more_speed, _vidas, _cameraLookPauseGameOver;
		Frog* _frog;
		bool _key_pressed, _paused, _gameOver;
		std::list <DynamicObject*> _cars;
		std::list <TimberLog*> _timberLogs;
		Vector3 _carPauseSpeed, _timberLogsPauseSpeed;
        Message* _message;
		Vida* _vida;
		
		Camera* _camera;
		PerspectiveCamera* _perspectiveCamera;
		OrthogonalCamera* _orthogonalCamera;
		OrthogonalCamera* _vidasCamera;
		
		Vector3* _positionBefore;

		Vector3* _eyePosition; // Camera position
		Vector3* _targetPosition; // Where camera is looking at
		Vector3* _upVector; // Target up vector (describes the camera rotation)
		GLfloat _distance; // Dintance from camera (eye) to target;
		GLfloat _angle; // Camera's angle rotation
		
		DirectedLightSource* _mainAmbientLight;
		PositionedLightSource* _lightPosts[6];
		PositionedLightSource* _headLight;
		
	public:
		GameManager();
		~GameManager();
    
        /* Game manager */
        void init();
        void pause();
        void unpause();
        void resetPositions(int mode);
        void restart();
        void gameOver();
    
        /* Window manipulation */
		void display();
		void reshape(GLsizei w, GLsizei h);
    
        /* Keyboard manager */
		void keyPressed(unsigned char key, int x, int y);
		void keyUp(unsigned char key, int x, int y);
    
        /* Time manager */
		bool onTimer(double time);
		void idle();
		void update(double delta_t);
    
        /* Collisions manager */
        void killFrog();
        void resetSpeed(int mode);
        int testFrogOutOfRange();
        void testSpeedIncrease();
        int testRammedFrog();
        int testOnTheRiver();
        bool topInsideRiver();
        bool bottomInsideRiver();
		bool topRiverside();
		bool bellyRiverside();
        void testCollisions(Vector3* frogPrev);
        bool testCollisionTimberlog();
        bool singleCollisionTimberlog(DynamicObject* object, float* box_frog);
        bool testDieFrog();
    
        /* Objects manager */
		void giveSpeedTimberlog();
        bool frogInsideTimberlog();
        void objectsRandomizer(DynamicObject* object);
        void testLimits(DynamicObject* object);
		void timeLess();
    
        /* Cameras manager */
		Vector3* getEyePosition();
		void updateThirdCameraView();

        /* Lights manager */
		void initMainAmbientLight();
		void initLightPosts();
        void updateHeadLightPosition();
};

#endif /* defined(__CG_labs__GameManager__) */
