//
//  GameManager.cpp
//  CG_labs
//
//  Created by Tomás Alves on 03/10/14.
//
//

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

#include <list>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include "GameManager.h"
#include "River.h"
#include "Riverside.h"
#include "Road.h"
#include "Roadside.h"
#include "Frog.h"
#include "Car.h"
#include "TimberLog.h"
#include "Camera.h"
#include "PerspectiveCamera.h"
#include "OrthogonalCamera.h"
#include "LightSource.h"
#include "DirectedLightSource.h"
#include "PositionedLightSource.h"
#include "Texture.h"
#include "Vida.h"


#define GAMEOVER 1
#define PAUSE 0

Texture* tex_water;
Texture* tex_road;
Texture* tex_roadside;
Texture* tex_riverside;
Texture* tex_timberlog;
Texture* tex_frog;
Texture* tex_pause;
Texture* tex_game_over;
Texture* tex_eye;

GameManager::GameManager() {
	_tant = 0;
	_tact = 0;
	_delta = 0;
    _more_speed = 1;
	_frog = new Frog(new Vector3(0.0, -7.0, 0));
	_perspectiveCamera  = new PerspectiveCamera();
	_orthogonalCamera = new OrthogonalCamera();
	_vidasCamera= new OrthogonalCamera();
	_camera = _orthogonalCamera;
	_cameraLook = 1;
	_eyePosition = new Vector3(0.0, -15.0, 8.0);
	_targetPosition = new Vector3(0.0, 0.0, 0.0);
	_upVector = new Vector3(0.0, 0.0, 1.0);
	_distance = 15;
	_angle = 0.0;
	_key_pressed = false;
	_vidas=5;
	_paused=false;
    _gameOver=false;
    _message=new Message();
	_vida=new Vida(new Vector3(-10.0, -8.5, 0));
    _cameraLookPauseGameOver = 1;
	
	_headLight = new PositionedLightSource(GL_LIGHT7);
	
		// Top lane
		_cars.push_back(new Car(new Vector3(-15.0,-1.3, 0.0)));
		_cars.push_back(new Car(new Vector3(-30.0, -1.3, 0.0)));
		_cars.push_back(new Car(new Vector3(-40.0, -1.3, 0.0)));
		
		// Middle lane
		_cars.push_back(new Car(new Vector3(15.0,-3.2, 0.0)));
		_cars.push_back(new Car(new Vector3(31.0,-3.2, 0.0)));
		_cars.push_back(new Car(new Vector3(23.0,-3.2, 0.0)));
		
		// Bottom lane
		_cars.push_back(new Car(new Vector3(-11.0,-5.1, 0.0)));
		_cars.push_back(new Car(new Vector3(-24.0,-5.1, 0.0)));
		_cars.push_back(new Car(new Vector3(-30.0,-5.1, 0.0)));
		
        // Top lane
		_timberLogs.push_back(new TimberLog(new Vector3(16.0, 6.90, -0.09)));
		_timberLogs.push_back(new TimberLog(new Vector3(27.0, 6.90, -0.09)));
		_timberLogs.push_back(new TimberLog(new Vector3(34.0, 6.90, -0.09)));
	
        // Top middle lane
		_timberLogs.push_back(new TimberLog(new Vector3(-13.0, 5.40, -0.09)));
		_timberLogs.push_back(new TimberLog(new Vector3(-20.0, 5.40, -0.09)));
		_timberLogs.push_back(new TimberLog(new Vector3(-27.0, 5.40, -0.09)));
		
        // Bottom middle lane
		_timberLogs.push_back(new TimberLog(new Vector3(14.0, 3.90, -0.09)));
		_timberLogs.push_back(new TimberLog(new Vector3(23.0, 3.90, -0.09)));
		_timberLogs.push_back(new TimberLog(new Vector3(31.0, 3.90, -0.09)));

        // Bottom lane
		_timberLogs.push_back(new TimberLog(new Vector3(-8.0, 2.40, -0.09)));
		_timberLogs.push_back(new TimberLog(new Vector3(-19.0, 2.40, -0.09)));
		_timberLogs.push_back(new TimberLog(new Vector3(-29.0, 2.40, -0.09)));
	
}

GameManager::~GameManager() {
}

/* --------------------------------------- */
/* --------------------------------------- */
/* ------- GAME MANAGER START KIT--------- */
/* --------------------------------------- */
/* --------------------------------------- */

void GameManager::init(){
    _game_objects.push_back(new River());
    _game_objects.push_back(new Riverside());
    _game_objects.push_back(new Road());
    _game_objects.push_back(new Roadside());

    // Setting the speed to the cars.
    for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
        if((*object)->getPosition()->getX() > 0) {
            (*object)->setSpeed(-0.004, 0.0, 0.0);
            (*object)->setDirection(-1, 0,0);
        }
        else {
            (*object)->setSpeed(0.004, 0.0, 0.0);
            (*object)->setDirection(1, 0,0);
        }
    }
    
    // Setting the speed to the timber logs.
    for( std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
        if( (*object)->getPosition()->getX() > 0) {
            (*object)->setSpeed(-0.002, 0.0, 0.0);
            (*object)->setDirection(-1, 0,0);
        }
        else {
            (*object)->setSpeed(0.002, 0.0, 0.0);
            (*object)->setDirection(1, 0,0);
        }
    }

    
	initMainAmbientLight();
	initLightPosts();
    
    glEnable(GL_TEXTURE_2D);
    tex_water = Texture::loadBMP("river.bmp");
    if(!tex_water) { std::cout << "I failed to load the river bmp." << endl; }
    tex_road = Texture::loadBMP("road.bmp");
    if(!tex_road) { std::cout << "I failed to load the road bmp." << endl; }
    tex_roadside = Texture::loadBMP("calcada.bmp");
    if(!tex_roadside) { std::cout << "I failed to load the roadside bmp." << endl; }
    tex_riverside = Texture::loadBMP("riverside.bmp");
    if(!tex_riverside) { std::cout << "I failed to load the riverside bmp." << endl; }
    tex_timberlog = Texture::loadBMP("timber.bmp");
    if(!tex_timberlog) { std::cout << "I failed to load the timberlog bmp." << endl; }
    tex_frog = Texture::loadBMP("frog.bmp");
    if(!tex_frog) { std::cout << "I failed to load the frog bmp." << endl; }
    tex_pause = Texture::loadBMP("pause.bmp");
    if(!tex_pause) { std::cout << "I failed to load the pause bmp." << endl; }
    tex_game_over = Texture::loadBMP("game_over.bmp");
    if(!tex_game_over) { std::cout << "I failed to load the game over bmp." << endl; }
    tex_eye = Texture::loadBMP("eye.bmp");
    if(!tex_eye) { std::cout << "I failed to load the eye bmp." << endl; }
    glDisable(GL_TEXTURE_2D);

}

/* --------------------------------------- */
/* --------------------------------------- */
/* -------- WINDOW MANIPULATION ---------- */
/* --------------------------------------- */
/* --------------------------------------- */

void GameManager::display(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	if(_cameraLook!=1){
		
		if(_cameraLook==3) updateThirdCameraView();
		_camera->computeVisualizationMatrix(_eyePosition->getX(), _eyePosition->getY(), _eyePosition->getZ(),
							_targetPosition->getX(), _targetPosition->getY(), _targetPosition->getZ(),
								_upVector->getX(), _upVector->getY(), _upVector->getZ());
		
		
	}
	
	
	glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);	 //specifies which material parameters track the current color
	glEnable(GL_NORMALIZE);
	
	glPushMatrix();
    
    std::list<StaticObject*>::iterator object=_game_objects.begin();
    (*object)->draw(tex_water);
    object++;
    (*object)->draw(tex_riverside);
    object++;
    (*object)->draw(tex_road);
    object++;
    (*object)->draw(tex_roadside);
    object++;
		
		for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
					(*object)->draw(tex_timberlog);
		}
		
		_frog->draw(tex_frog);
		
		for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
					(*object)->draw();
		}
    for(int i=0; i<6; i++){
        _lightPosts[i]->drawLightPost();
        _lightPosts[i]->shine();
    }
    
    _mainAmbientLight->shine();
    
    updateHeadLightPosition();
    
    glPopMatrix();

	
    glMatrixMode(GL_PROJECTION);
		glPushMatrix();
                glLoadIdentity();
				_vidasCamera->computeProjectionMatrix();
				
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
    
                if(_paused){
                        _message->draw(tex_pause);
                }
                else if (_gameOver){
                        _message->draw(tex_game_over);
                }
    
                for(int i=0; i<_vidas; i++){
                    _vida->draw(i, tex_frog, tex_eye);
                }
    
                glMatrixMode(GL_PROJECTION);
		glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
}

void GameManager::reshape(GLsizei w, GLsizei h){
     
    float xmin = -11.0, xmax = 11.0, ymin = -9,  ymax = 9.;
    float ratio = (xmax-xmin)/ (ymax-ymin);
    float aspect = (float) w / h;
     
    if(aspect > ratio)
        glViewport((w-h*ratio)/2,0, h*ratio, h);
    else
        glViewport(0,(h-w/ratio)/2, w, w/ratio);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    _perspectiveCamera->update(60, aspect, ratio, 0.1, 120);
    _orthogonalCamera->update(xmin, xmax, ymin, ymax, -5, 10, ratio, aspect);
    _vidasCamera->update(xmin, xmax, ymin, ymax, -5, 10, ratio, aspect);
         
    _camera->computeProjectionMatrix();
    _camera->computeVisualizationMatrix(_eyePosition->getX(), _eyePosition->getY(), _eyePosition->getZ(),
                            _targetPosition->getX(), _targetPosition->getY(), _targetPosition->getZ(),
                                _upVector->getX(), _upVector->getY(), _upVector->getZ());
    
}

/* --------------------------------------- */
/* --------------------------------------- */
/* --------- TIME MANIPULATION ----------- */
/* --------------------------------------- */
/* --------------------------------------- */

bool GameManager::onTimer(double time){
	return false;
}

void GameManager::idle(){
    _positionBefore = _frog->getPosition();
    _tact = glutGet(GLUT_ELAPSED_TIME);
    _delta = _tact - _tant;
    update(_delta);
    _tant = _tact;
    testCollisions(_positionBefore);
    timeLess();
    if(!_key_pressed) { giveSpeedTimberlog(); }
}

/* --------------------------------------- */
/* --------------------------------------- */
/* ------------- COLLISIONS -------------- */
/* --------------------------------------- */
/* --------------------------------------- */
/* ------- COLLISION MAIN FUNCTION ------- */
/* --------------------------------------- */

// Collisions are only analised in 2D, i.e (x, y).
// There are three things that must be test
//  1. If the frog collides with the limits of the world
//  2. If the frog collides with a car
//  3. If the frog is safe in the river
void GameManager::testCollisions(Vector3* frogPrev) {
    if(testFrogOutOfRange()) { _frog->setPosition(frogPrev->getX(), frogPrev->getY(), frogPrev->getZ()); }
    if(testRammedFrog()) { killFrog(); return; }
    if(testOnTheRiver()) { killFrog(); return; }
}

// 1. This function checks if the frog's box limits are equal or bigger than the field's limits.
//  If it is, the position must be altered to the previous one.
int GameManager::testFrogOutOfRange() {
    float* box_frog = _frog->boxLimits();
    // Left Side
    if (box_frog[0] <= -11.00) {
        return 1;
    }
    // Right Side
    else if (box_frog[1] >= 11.00) {
        return 1;
    }
    // Down Side
    else if (box_frog[2] <= -8) {
        return 1;
    }
    // Up Side
    else if (box_frog[3] >= 8.9) {
        return 1;
    }
    return 0;
}

// 2. This function tries to find a collision between the frog and an active car. The collision is true if the two boxes from each object collide.
//  If there is one, the frog is dead. The function void GameManager::killFrog() is called and deals with the collision.
int GameManager::testRammedFrog(){
    float* box_frog = _frog->boxLimits();
    for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
        float* box_car = (*object)->boxLimits();
        if (box_frog[0] <= box_car[1] && box_frog[1] >= box_car[0] && box_frog[2] <= box_car[3] && box_frog[3] >= box_car[2]) {
            return 1;
        }
    }
   return 0;
}

// 3. This function checks activity in the river and all the collisions that may or not happen.
int GameManager::testOnTheRiver() {
    // Firstly, it checks if the frog is touching in the river.
    if (topInsideRiver()) {
		// Checks if the frog's center is above the river's top line.
        if(bellyRiverside()) {
            //Win condition
            return 0;
        }
        // If it is, we now check if the frog is colliding with any of the existing timberlogs.
        if (testCollisionTimberlog()){
            // It's known that it's colliding, so it checks if the frog's center is already on the top of the timber log
            if(frogInsideTimberlog()){
                // If the frog has it's center on the top of a timber log, everything is perfect, the function returns.
                return 0;
            }
			// Checks if the frog's head is above the river's top line.
			else if(topRiverside()) {
				return 0;
			}
            else {
                // If it isn't, it's possible that the frog must die. Therefore, we check if the frog is trying to move to the top of a timber log or not.
                if(bottomInsideRiver()){
                    // If it's bottom legs are already over the riverside, the frog must be killed due to the user's misdirection.
                    return 1;
                }
                else {
                    // If not, the frog is trying to enter in the timber log and must not be killed.
                    return 0;
                }			
            }
        }
        // Lastly, knowing that the frog has its head over the river, there must be a final test to check if the frog has its head on the top of some timber log or no. If it's true that he hasn't on the top of any timber log, the frog must be killed.
        else if (testDieFrog()) {
            return 1;
        }
    }
    else {
        return 0;
    }
    return 0;
}

/* --------------------------------------- */
/* ----- COLLISION UTILITY FUNCTIONS ----- */
/* --------------------------------------- */

// Checks if the frog's head is over the river which lowest y value is 1.5f.
bool GameManager::topInsideRiver() {
    return (_frog->boxLimits())[3] >= 1.5;
}

// Checks if the frog's bottom legs are over the river which lowest y value is 1.5f.
bool GameManager::bottomInsideRiver() {
    return (_frog->boxLimits())[2] >= 1.5;
}

// Checks if the frog's head is outside the river which highest y value is 7.8f.
bool GameManager::topRiverside() {
    return (_frog->boxLimits())[3] >= 7.8;
}

// Checks if the frog's center are outside the river which highest y value is 7.8f.
bool GameManager::bellyRiverside() {
    return _frog->getPosition()->getY() >= 7.8;
}

// Checks if the frog must be killed or not. If its xmin and xmax are inside the xmin and xmax of any timber log, the frog is safe. Else, it dies.
bool GameManager::testDieFrog(){
    float* box_frog = _frog->boxLimits();
    for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
        float* box_log = (*object)->boxLimits();
        if (box_frog[0] <= box_log[1] && box_frog[1] >= box_log[0]) {
            return false;
        }
    }
    return true;
}

// Checks if the frog collides with any of the timber logs and returns true if it does, false otherwise.
bool GameManager::testCollisionTimberlog() {
    bool touching_T = false;
    float* box_frog = _frog->boxLimits();
    for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
        touching_T = singleCollisionTimberlog((*object), box_frog);
        if(touching_T) {
            return true;
        }
    }
    return false;
}

// Checks if the frog collides with a specific timber log and returns true if it does, false otherwise.
bool GameManager::singleCollisionTimberlog(DynamicObject* object, float* box_frog) {
    float* box_log = object->boxLimits();
    if (box_frog[0] <= box_log[1] && box_frog[1] >= box_log[0] && box_frog[2] <= box_log[3] && box_frog[3] >= box_log[2]) {
        return true;
    }
    return false;
}

// Checks if the frog's center is inside any timber log and returns true if it does, false otherwise.
bool GameManager::frogInsideTimberlog() {
    for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
        float* box_log = (*object)->boxLimits();
        if (_frog->getPosition()->getX() <= box_log[1] && _frog->getPosition()->getX() >= box_log[0] && _frog->getPosition()->getY() <= box_log[3] && _frog->getPosition()->getY() >= box_log[2]) {
            return true;
        }
    }
    return false;
}

// Kills the frog setting it up to the original position and direction.
void GameManager::killFrog() {
    _frog->setPosition(0.0, -7.0, 0.0);
    _frog->setToRotate(0.0, 1.0, 0.0);
    _frog->setSpeed(0.0, 0.0, 0.0);
    _vidas--;
    if(_vidas==0){
        gameOver();
    }	
}

/* --------------------------------------- */
/* --------------------------------------- */
/* ---- DYNAMIC OBJECTS MANIPULATION ----- */
/* --------------------------------------- */
/* --------------------------------------- */

void GameManager::objectsRandomizer(DynamicObject* object){
	float random;
    int direction=1;
    float speed = object->getSpeed().getX();
    if(speed<0) direction = -1;
    random=(rand() % 1) / (speed*direction);
    while(random> 4/(speed*direction)){
        random=(rand() % 1) / (speed*direction);
        
    }
    object->setTime(random); // Defines how much time will it take to recreate the object
    object->setPosition(-20*direction, object->getPosition()->getY(), object->getPosition()->getZ()); // Defines a position out of the viewport to create the object
}

void GameManager::testLimits(DynamicObject* object){
    float *limits, speed;
    speed=object->getSpeed().getX();
    limits = object->boxLimits(); 
    if(limits[0]>=11 && speed>0){ // Tests the right limit of the window
        objectsRandomizer(object);
    }
	else if(limits[1]<=-11 && speed<0){ // Tests the left limit of the window
		objectsRandomizer(object);
	}
}

void GameManager::timeLess(){
    for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
        if((*object)->getTime()>0){
            (*object)->setTime((*object)->getTime()-1);
        }
        
    }
    for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
        if((*object)->getTime()>0){
            (*object)->setTime((*object)->getTime()-1);
        }
    }
}

void GameManager::giveSpeedTimberlog() {
    for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
        float* box_log = (*object)->boxLimits();
        if (_frog->getPosition()->getX() <= box_log[1] && _frog->getPosition()->getX() >= box_log[0] && _frog->getPosition()->getY() <= box_log[3] && _frog->getPosition()->getY() >= box_log[2]) {
            _frog->setSpeed((*object)->getSpeed().getX(), 0.0, 0.0);
            return;
        }
    }
}

void GameManager::testSpeedIncrease () {
    // Checks if it's time to pump up the speed of both cars and timberlogs.
    // Updates each 100 seconds.
    // new_speed <- base_speed * i
    if(_paused || _gameOver) return;
    for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
		float speed = (*object)->getSpeed().getX();
		int direction=1;
		if (speed<0) direction =-1;
            (*object)->setSpeed(speed+0.0004*direction, 0.0, 0.0);
        }
    for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
			float speed = (*object)->getSpeed().getX();
			int direction=1;
			if (speed<0) direction =-1;
            (*object)->setSpeed(speed+0.0004*direction
            , 0.0, 0.0);
     }
        _more_speed++;
        std::cout << "DEBUGGER: Speed Increase" << '\n' << "_____Dynamic obstacles are " << _more_speed << " faster than the start of the game." << '\n';
}

void GameManager::update(double delta_t){
    if(_paused || _gameOver) { glutPostRedisplay(); return; }
		for(std::list<StaticObject*>::iterator object=_game_objects.begin(); object != _game_objects.end(); object++){
					(*object)->update(delta_t);
		}
	
		for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
					(*object)->update(delta_t);
					testLimits(*object);
		}
		for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
					(*object)->update(delta_t);
					testLimits(*object);
		}

		_frog->update(delta_t);
				
		glutPostRedisplay();
}

/* --------------------------------------- */
/* --------------------------------------- */
/* -------- CAMERAS MANIPULATION --------- */
/* --------------------------------------- */
/* --------------------------------------- */

void GameManager::updateThirdCameraView(){
		_eyePosition->setX(_frog->getPosition()->getX());
		_eyePosition->setY(_frog->getPosition()->getY() - 5.0 + 2.0);
		_eyePosition->setZ(_frog->getPosition()->getZ() + 8.0 - 5.0);
		
		_targetPosition->setX(_frog->getPosition()->getX());
		_targetPosition->setY(_frog->getPosition()->getY() + 5.0);
		_targetPosition->setZ(_frog->getPosition()->getZ());
}

/* --------------------------------------- */
/* --------------------------------------- */
/* -------- LIGHTS MANIPULATION ---------- */
/* --------------------------------------- */
/* --------------------------------------- */

void GameManager::initMainAmbientLight(){
    
    GLfloat amb[] = {0.2f, 0.2f, 0.2f, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);		// Adds low ambient light (dark / night mode)
    
    _mainAmbientLight = new DirectedLightSource(GL_LIGHT0);
    _mainAmbientLight->setAmbient(new Vector4(0.25, 0.25, 0.25, 1.0));	// Sets light that comes from all directions to "day mode"
    _mainAmbientLight->setDiffuse(new Vector4(0.8, 0.8, 0.8, 1.0));	// Diffuse reflection reflects light in all directions
    _mainAmbientLight->setSpecular(new Vector4(1.0, 1.0, 1.0, 1.0)); 	// Sets the specular color (white)
    _mainAmbientLight->setDirection(new Vector4(10.0, -10.0, 10.0, 0.0)); // Direction from which the light is shining
    
}

void GameManager::initLightPosts(){

    _lightPosts[0] = new PositionedLightSource(GL_LIGHT1);
    _lightPosts[1] = new PositionedLightSource(GL_LIGHT2);
    _lightPosts[2] = new PositionedLightSource(GL_LIGHT3);
    _lightPosts[3] = new PositionedLightSource(GL_LIGHT4);
    _lightPosts[4] = new PositionedLightSource(GL_LIGHT5);
    _lightPosts[5] = new PositionedLightSource(GL_LIGHT6);
    
    
    // Positions from which the light post is shining
    _lightPosts[0]->setPosition(new Vector4(-5.0, 0.7, 4.0, 1.0));	// Center left
    _lightPosts[1]->setPosition(new Vector4(5.0, 0.7, 4.0, 1.0));	// Center right
    _lightPosts[2]->setPosition(new Vector4(-5.0, -7.0, 4.0, 1.0));	// Bottom left
    _lightPosts[3]->setPosition(new Vector4(5.0, -7.0, 4.0, 1.0));	// Bottom right
    _lightPosts[4]->setPosition(new Vector4(-5.0, 8.4, 4.0, 1.0));	// Top left
    _lightPosts[5]->setPosition(new Vector4(5.0, 8.4, 4.0, 1.0));	// Top right
    
    for(int i=0; i<6; i++){
        _lightPosts[i]->setAmbient(new Vector4(0.0, 0.0, 0.0, 1.0));	// Sets light that comes from all directions to "day mode"
        _lightPosts[i]->setDiffuse(new Vector4(0.8,0.8,0.6, 1.0));      // Diffuse reflection reflects light in all directions
        _lightPosts[i]->setSpecular(new Vector4(0.8,0.8,0.6, 1.0)); 	// Sets the specular color (white)
        
        _lightPosts[i]->setDirection(new Vector4(0.0, 0.0, -1.0, 1.0));	// Direction where the spotlight is pointing to
        _lightPosts[i]->setCutOff(90);                                  // 0~90º  intensity distribution of the light
        _lightPosts[i]->setExponent(3);                                 // 0~128  maximum spread angle of the light source
    }
}

void GameManager::updateHeadLightPosition(){
    
    Vector3* direction = _frog->getDirection();
    
    _headLight->setAmbient(new Vector4(0.0, 0.0, 0.0, 1.0));
    _headLight->setDiffuse(new Vector4(1.0, 1.0, 1.0, 1.0));
    _headLight->setSpecular(new Vector4(1.0, 1, 1, 1.0));
    
    _headLight->setCutOff(30);
    _headLight->setExponent(40);
    
    if(direction->getY()){	// Frog's head is pointing North or South
        _headLight->setDirection(new Vector4(0.0, direction->getY() * 4.0, -2.0, 0.0));
        _headLight->setPosition(new Vector4(_frog->getPosition()->getX(), _frog->getPosition()->getY() - (direction->getY() * 1.5), 2, 1.0));
    }
    else{	// Frog's head is pointing East or West
        _headLight->setDirection(new Vector4(direction->getX() * 4.0, 0.0, -2.0, 0.0));
        _headLight->setPosition(new Vector4(_frog->getPosition()->getX() - (direction->getX() * 1.5), _frog->getPosition()->getY(), 2, 1.0));
    }
    _headLight->shine();
}

/* --------------------------------------- */
/* --------------------------------------- */
/* ---------- GAME CONTROLLER ------------ */
/* --------------------------------------- */
/* --------------------------------------- */

void GameManager::resetSpeed(int mode){
    _frog->setSpeed(0.0, 0.0, 0.0);
    if (mode){
        for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
            float speed = (*object)->getSpeed().getX();
            (*object)->setSpeed(0.004* (*object)->getDirection().getX(), 0.0, 0.0);
        }
        for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
            
            (*object)->setSpeed(0.002*(*object)->getDirection().getX(), 0.0, 0.0);
        }
        _more_speed=1;
    }
    else{
        for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
            float speed = (*object)->getSpeed().getX();
            (*object)->setSpeed(0.0, 0.0, 0.0);
        }
        for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
            
            (*object)->setSpeed(0.0, 0.0, 0.0);
        }
        _more_speed=1;
    }
}

void GameManager::pause(){
    _frog->setSpeed(0,0,0);
    // Saving the cars' speed
    for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
        _carPauseSpeed.set((*object)->getSpeed().getX(),(*object)->getSpeed().getY(), (*object)->getSpeed().getZ());
        (*object)->setSpeed(0, 0.0, 0.0);
    }
    // Saving the timber logs' speed
    for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
        _timberLogsPauseSpeed.set((*object)->getSpeed().getX(),(*object)->getSpeed().getY(), (*object)->getSpeed().getZ());
        (*object)->setSpeed(0, 0.0, 0.0);
    }
}

void GameManager::unpause(){
        for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
        (*object)->setSpeed(_carPauseSpeed.getX()*(*object)->getDirection().getX(),_carPauseSpeed.getY()*(*object)->getDirection().getY(), _carPauseSpeed.getZ()*(*object)->getDirection().getZ());
        
    }
    for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
        (*object)->setSpeed(_timberLogsPauseSpeed.getX()*(*object)->getDirection().getX(), _timberLogsPauseSpeed.getY()*(*object)->getDirection().getY(), _timberLogsPauseSpeed.getZ()*(*object)->getDirection().getZ());
    }
}

void GameManager::restart(){
    _vidas=5;
    resetSpeed(1);
    resetPositions(1);
}

void GameManager::resetPositions(int mode){

    if(mode){
        std::list<Vector3*> carPositions;
        std::list<Vector3*> timberLogsPositions;
        carPositions.push_back(new Vector3(-15.0,-1.3, 0.0));
        carPositions.push_back(new Vector3(-30.0, -1.3, 0.0));
        carPositions.push_back(new Vector3(-40.0, -1.3, 0.0));
        carPositions.push_back(new Vector3(15.0,-3.2, 0.0));
        carPositions.push_back(new Vector3(31.0,-3.2, 0.0));
        carPositions.push_back(new Vector3(23.0,-3.2, 0.0));
        carPositions.push_back(new Vector3(-11.0,-5.1, 0.0));
        carPositions.push_back(new Vector3(-24.0,-5.1, 0.0));
        carPositions.push_back(new Vector3(-30.0,-5.1, 0.0));
        
        timberLogsPositions.push_back(new Vector3(16.0, 6.90, -0.09));
        timberLogsPositions.push_back(new Vector3(27.0, 6.90, -0.09));
        timberLogsPositions.push_back(new Vector3(34.0, 6.90, -0.09));
        timberLogsPositions.push_back(new Vector3(-13.0, 5.40, -0.09));
        timberLogsPositions.push_back(new Vector3(-20.0, 5.40, -0.09));
        timberLogsPositions.push_back(new Vector3(-27.0, 5.40, -0.09));
        timberLogsPositions.push_back(new Vector3(14.0, 3.90, -0.09));
        timberLogsPositions.push_back(new Vector3(23.0, 3.90, -0.09));
        timberLogsPositions.push_back(new Vector3(31.0, 3.90, -0.09));
        timberLogsPositions.push_back(new Vector3(-8.0, 2.40, -0.09));
        timberLogsPositions.push_back(new Vector3(-19.0, 2.40, -0.09));
        timberLogsPositions.push_back(new Vector3(-29.0, 2.40, -0.09));
        
        std::list<Vector3*>::iterator carPosition=carPositions.begin();
        for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
            (*object)->setPosition((*carPosition));
            carPosition++;
        }
        std::list<Vector3*>::iterator timberlogPosition=timberLogsPositions.begin();
        for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
            (*object)->setPosition((*timberlogPosition));
            timberlogPosition++;
        }
    }
    else{
        for(std::list<DynamicObject*>::iterator object=_cars.begin(); object != _cars.end(); object++){
            (*object)->setPosition(new Vector3(-50, 0, 0));
        }
        for(std::list<TimberLog*>::iterator object=_timberLogs.begin(); object != _timberLogs.end(); object++){
            (*object)->setPosition(new Vector3(-50, 0, 0));
        }
    }
}

void GameManager::gameOver(){
    _gameOver=true;
    resetSpeed(0);
    resetPositions(0);
}

/* --------------------------------------- */
/* --------------------------------------- */
/* ---------- KEYBOARD EVENTS ------------ */
/* --------------------------------------- */
/* --------------------------------------- */

void GameManager::keyPressed(unsigned char key, int x, int y){
    
    unsigned char keyPressed = tolower(key);
    
    switch(keyPressed) {
        case 'q':
            // Up
            if(!_paused && !_gameOver){
                _frog->setSpeed(0.0, 0.005, 0.0);
                _frog->setToRotate(0.0, 1.0, 0.0);
                _key_pressed = true;
            }
            break;
            
        case 'a':
            // Down
            if(!_paused && !_gameOver){
                _frog->setSpeed(0.0, -0.005, 0.0);
                _frog->setToRotate(0.0, -1.0, 0.0);
                _key_pressed = true;
            }
            break;
            
        case 'o':
            // Left
            if(!_paused && !_gameOver){
                _frog->setSpeed(-0.005, 0.0, 0.0);
                _frog->setToRotate(-1.0, 0.0, 0.0);
                _key_pressed = true;
            }
            break;
            
        case 'p':
            // Right
            if(!_paused && !_gameOver){
                _frog->setSpeed(0.005, 0.0, 0.0);
                _frog->setToRotate(1.0, 0.0, 0.0);
                _key_pressed = true;
            }
            break;
            
        case '1':
            if(!_paused && !_gameOver){
                if(_cameraLook != 1){
                    _camera = _orthogonalCamera;
                    _cameraLook = 1;
                    _camera->computeProjectionMatrix();
                    _camera->computeVisualizationMatrix(_eyePosition->getX(), _eyePosition->getY(), _eyePosition->getZ(),
                                                        _targetPosition->getX(), _targetPosition->getY(), _targetPosition->getZ(),
                                                        _upVector->getX(), _upVector->getY(), _upVector->getZ());
                }
            }
            break;
            
        case '2':
            if(!_paused && !_gameOver){
                if(_cameraLook != 2){
                    glEnable(GL_DEPTH_TEST);
                    _camera = _perspectiveCamera;
                    _cameraLook = 2;
                    
                    _eyePosition->set(0.0, -15.0, 8.0);
                    _targetPosition->set(0.0, 0.0, 0.0);
                    
                    _camera->computeProjectionMatrix();
                }
            }
            break;
            
        case '3':
            if(!_paused && !_gameOver){
                if(_cameraLook != 3){
                    glEnable(GL_DEPTH_TEST);
                    _camera = _perspectiveCamera;
                    _cameraLook = 3;
                    _camera->computeProjectionMatrix();
                    
                }
            }
            break;
            
        case 't':
            if(!_paused && !_gameOver){
                if(_cameraLook == 2){ // If it's the prespective camera, we don't want it so spin or change the values of the orthogonal one.
                    _angle -= 0.1f;
                    _eyePosition->setY(_targetPosition->getY() - _distance * cos(_angle));
                    _eyePosition->setX(_targetPosition->getX() + _distance * sin(_angle));
                    
                    
                    _camera->computeVisualizationMatrix(_eyePosition->getX(), _eyePosition->getY(), _eyePosition->getZ(),
                                                        _targetPosition->getX(), _targetPosition->getY(), _targetPosition->getZ(),
                                                        _upVector->getX(), _upVector->getY(), _upVector->getZ());
                }
            }
            break;
            
        case 'y':
            if(!_paused && !_gameOver){
                if(_cameraLook == 2){ // If it's the prespective camera, we don't want it so spin or change the values of the orthogonal one.
                    _angle += 0.1f;
                    
                    _eyePosition->setY(_targetPosition->getY() - _distance * cos(_angle));
                    _eyePosition->setX(_targetPosition->getX() + _distance * sin(_angle));
                    
                    _camera->computeVisualizationMatrix(_eyePosition->getX(), _eyePosition->getY(), _eyePosition->getZ(),
                                                        _targetPosition->getX(), _targetPosition->getY(), _targetPosition->getZ(),
                                                        _upVector->getX(), _upVector->getY(), _upVector->getZ());
                }
            }
            break;
            
        case 'l':
            if(!_paused && !_gameOver){
                if(glIsEnabled(GL_LIGHTING)){
                    glDisable(GL_LIGHTING);
                    
                }
                else{
                    glEnable(GL_LIGHTING);
                }
            }
            break;
            
        case 'n':
            if(!_paused && !_gameOver){
                if(glIsEnabled(GL_LIGHTING)){
                    if(_mainAmbientLight->getState()){
                        _mainAmbientLight->setState(false);
                        glDisable(_mainAmbientLight->getNum());
                    }
                    else{
                        _mainAmbientLight->setState(true);
                        glEnable(_mainAmbientLight->getNum());
                    }
                    
                    if(_lightPosts[0]->getState()){
                        for(int i=0; i<6; i++){
                            _lightPosts[i]->setState(false);
                            _lightPosts[i]->drawLampSphereEmission(0.0, 0.0, 0.0);
                            glDisable(_lightPosts[i]->getNum());
                        }
                    }
                }
            }
            break;

        case 'c':
            if(!_paused && !_gameOver){
                if(glIsEnabled(GL_LIGHTING) && !_mainAmbientLight->getState()){
                    if(_lightPosts[0]->getState()){
                        for(int i=0; i<6; i++){
                            _lightPosts[i]->setState(false);
                            _lightPosts[i]->drawLampSphereEmission(0.0, 0.0, 0.0);
                            glDisable(_lightPosts[i]->getNum());
                        }
                    }
                    else{
                        for(int i=0; i<6; i++){
                            _lightPosts[i]->setState(true);
                            _lightPosts[i]->drawLampSphereEmission(0.4, 0.4, 0.4);
                            glEnable(_lightPosts[i]->getNum());
                        }
                    }
                }
            }
            break;
            
        case 'h': 
            if(!_paused && !_gameOver){
                if(glIsEnabled(GL_LIGHTING)){
                    if(_headLight->getState()){
                        _headLight->setState(false);
                        glDisable(_headLight->getNum());
                    }
                    else if(!_mainAmbientLight->getState()){
                        _headLight->setState(true);
                        glEnable(_headLight->getNum());
                        
                    }
                }
            }
            break;
            
        case 's':
            if (!_paused && !_gameOver){
//                pause();
                _paused=true;
            }
            else if(_paused && !_gameOver){
//                unpause();
                _paused=false;
            }
            break;
            
        case 'r':
            if(!_paused && _gameOver){
                _gameOver=false;
                restart();
            }
            break;
    }
}

void GameManager::keyUp(unsigned char key, int x, int y){
    _frog->setSpeed(0.0, 0.0, 0.0);
	_key_pressed = false;
}