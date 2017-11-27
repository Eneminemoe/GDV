#pragma once
#include "Drohne.h"
<<<<<<< HEAD
#include "Snowflake.h"
=======
#include "GL/SOIL.h"
>>>>>>> 95f1d3882cafdf20077f747f233c812e2791af19
#define CAMERASPEED 0.05f
#define SPEEDOBJECT .005f
#define ESCAPEKEY 27
#define GAMESPEED 2
#define SCROLLUP 3
#define SCROLLDOWN 4

enum direction {LEFT,RIGHT,UP,DOWN,FORWARD,BACKWARD};


void RenderScene();
void Reshape(int,int);
void square(float,float,float);
void Wuerfel(GLfloat, GLfloat);
void getInput(unsigned char,int ,int);
void MouseFunc(int, int, int, int);
void MotionP(int , int);
void SpecialFunc(int, int , int );
void drawSnowMan();
void drawGrid();
void moveCameraKeyboard(float,direction);
void Animate(int);
void idle();
void moveDrone(int);
void drawTree(float, int);