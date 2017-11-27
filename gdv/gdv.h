#pragma once
#include "Drohne.h"
#include "Snowflake.h"
#define CAMERASPEED 0.05f
#define SPEEDOBJECT 0.001f
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
