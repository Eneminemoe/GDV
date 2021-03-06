// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include "GL/freeglut.h"         //lädt alles für OpenGL
#include "gdv.h"



float angle = 0.0f;
double zoom = 0.1;
int globalwidth = 600;
int globalheight = 600;
int oldTime = 0;
int frames =0;
int timebase = 0;
GLdouble camerapositionX = 0.0f;
GLdouble camerapositionY = 2.0f;
GLdouble camerapositionZ = 0.0f;
GLdouble cameraTargetX = 5.0f;
GLdouble cameraTargetY = 1.0f;
GLdouble cameraTargetZ = -5.0f;
GLdouble upX = 0.0f;
GLdouble upY = 1.0f;
GLdouble upZ = 0.0f;

GLdouble left = -1.0f/zoom;
GLdouble right = 1.0f/zoom;
GLdouble bottom = -1.0f/zoom;
GLdouble top = 1.0f/zoom;
GLdouble nearGL = 0.1f;
GLdouble farGL = 100.0f;

GLdouble fieldOfView = 45.0f;
GLdouble aspectRatio = 1.0f;

GLfloat fRotation = 0.0;
GLfloat rotorDegree = 10.0;
GLfloat x1 = -4.0;
GLfloat y_first_drone = 0.0;
GLfloat x2 = 4.0;
GLfloat y2 = 4.0;



void Init()
{
	// Init Glut and create Window
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(globalwidth, globalheight);         // Fenster-Konfiguration
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Jens; Dennis");   // Fenster-Erzeugung
	
	//register callbacks
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);			 //ResizeFunktion bekanntmachen
	glutIdleFunc(idle); 
	glutMouseFunc(MouseFunc);
	glutPassiveMotionFunc(MotionP);
	glutSpecialFunc(SpecialFunc);
	glutKeyboardFunc(getInput);
	//glutTimerFunc(33, Animate, 0);  //FPS begrenzen
	
	//OpenGLInit
	glShadeModel(GL_SMOOTH); //Smooth rendering
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); //Background
	glClearDepth(1.0);
	
}

void RenderScene() //Zeichenfunktion
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
	ShowCursor(false);
	
	gluLookAt(camerapositionX,camerapositionY,camerapositionZ,
			  cameraTargetX  , cameraTargetY , cameraTargetZ,
				upX,			upY,			upZ);
	
	drawGrid();
	//Snowflake();




	glPushMatrix();
	glTranslatef(x1, y_first_drone, 0.0);
	Drohne(fRotation);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x2, y2, 0.0);
	Drohne(fRotation);
	glPopMatrix();
	
	glRotatef(angle, 1.0f, 0.0f, 0.0f);
	Wuerfel(.3f,0);
	glutSwapBuffers(); //with GLUT_DOUBLE using two buffers, changing happens here
}

void Reshape(int width, int height)
{
	// Hier finden die Reaktionen auf eine Veränderung der Größe des 
	// Graphikfensters statt

	if (height == 0)height = 1; //Prevent divide by zero
	float ratio = width / height;

	glViewport(0, 0, width, height); //Viewport to entire window

	globalwidth = width;
	globalheight = height;
	aspectRatio = globalwidth / globalheight;
	
	//Projection-Matrix wählen und zurücksetzen
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(fieldOfView, aspectRatio, nearGL, farGL);
	
	glMatrixMode(GL_MODELVIEW);

}

void Animate(int ms)
{
	angle += 0.2f *ms;
	if (angle == 360)angle = 0.0f;

	// Rotorblätter drehen
	fRotation = fRotation - rotorDegree; // Rotationswinkel aendern
	if (fRotation <= 0.0) {
		fRotation = fRotation + 360.0;
	}

}

void idle() {
	int t = glutGet(GLUT_ELAPSED_TIME); // Frame Rate Independent Animation 
	int passed = t - oldTime;
	
	//fps
	frames++;
	if (t - timebase > 1000) {
		std::cout << frames*1000/(t-timebase) << "FPS";
		timebase = t;
		frames = 0;
	}
	
	oldTime = t;
	Animate(passed);
	glutPostRedisplay();
}

void getInput(unsigned char key, int x, int y) {

	switch (key) {
	case ESCAPEKEY: 
		exit(0);
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	Init();
	glutMainLoop();
	
	
	
	
	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	//glutTimerFunc(33, Animate, 33);
	

	return 0;
}

void square(float size, float position, float positionZ) {

	glBegin(GL_POLYGON);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3f((-0.5 + position) *size, (-0.5 + position) *size, (-0.5 + positionZ) *size);
	glVertex3f((0.5 + position) * size, (-0.5 + position) * size, (-0.5 + positionZ) * size);
	glVertex3f((0.5 + position) * size, (0.5 + position) *size, (-0.5 + positionZ) * size);
	glVertex3f((-0.5 + position) * size, (0.5 + position) * size, (-0.5 + positionZ) * size);
	glEnd();
	

}

void Wuerfel(GLfloat fSeitenL, GLfloat position)
{
	glBegin(GL_POLYGON);   //Vorderseite
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);	//ROT
	glVertex3f(-fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glEnd();


	glBegin(GL_POLYGON);   //Rechte Seite
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);	//CYAN
	glVertex3f(+fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glEnd();


	glBegin(GL_POLYGON);   //Rueckseite
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); //CYAN
	glVertex3f(+fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glEnd();


	glBegin(GL_POLYGON);   //Linke Seite
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //ROT	
	glVertex3f(-fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glEnd();

	glBegin(GL_POLYGON);   //Deckflaeche
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); //CYAN
	glVertex3f(+fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-fSeitenL / 2.0f + position, +fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glEnd();

	glBegin(GL_POLYGON);   //Bodenflaeche
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, -fSeitenL / 2.0f - position);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //ROT
	glVertex3f(-fSeitenL / 2.0f + position, -fSeitenL / 2.0f + position, +fSeitenL / 2.0f - position);
	glEnd();

	return;
}

void MouseFunc(int button, int state, int x, int y)
// Maus-Tasten und -Bewegung abfragen
{
	GLfloat xMousePos = float(x);
	GLfloat yMousePos = float(y);
	if (button == SCROLLUP) {}
	if (button == SCROLLDOWN) {}



}

void MotionP(int x, int y)
// Maus-Bewegungen ohne gedrueckte Maus-Taste
{
	GLfloat xMousePos = float(x);
	GLfloat yMousePos = float(y);
	float angle_y = 0.0f;
	float angle_z = 0.0f;
	POINT mousePos;
	int mid_X = globalwidth >> 1;
	int mid_Y = globalheight >> 1;
	GetCursorPos(&mousePos);
	if ((mousePos.x == mid_X) && (mousePos.y == mid_Y)) return;
	SetCursorPos(mid_X, mid_Y);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angle_y = (float)((mid_X - mousePos.x)) / 1000;
	angle_z = (float)((mid_Y - mousePos.y)) / 1000;
	// The higher the value is the faster the camera looks around.
	cameraTargetY += angle_z * 2;

	// limit the rotation around the x-axis
	if ((cameraTargetY - camerapositionY) > 8)  cameraTargetY = camerapositionY + 8;
	if ((cameraTargetY - camerapositionY) <-8)  cameraTargetY = camerapositionY - 8;

	GLfloat tmpx = cameraTargetX - camerapositionX;
	GLfloat tmpz = cameraTargetZ - camerapositionZ;
	cameraTargetZ = (float)(camerapositionZ + sin(-angle_y)*tmpx + cos(-angle_y)*tmpz);
	cameraTargetX = (float)(camerapositionX + cos(-angle_y)*tmpx - sin(-angle_y)*tmpz);

	std::cout << xMousePos << ", " << yMousePos << std::endl;
	// RenderScene aufrufen.
	glutPostRedisplay();
}

void SpecialFunc(int key, int x, int y)
// Funktions- und Pfeil-Tasten abfragen
{
	GLfloat xMousePos = float(x);
	GLfloat yMousePos = float(y);
	

		switch (key) {
		case GLUT_KEY_LEFT:
			std::cout << "GLUT_KEY_LEFT " << camerapositionX << ", " << camerapositionZ << std::endl;
			moveCameraKeyboard(-CAMERASPEED,LEFT);
			break;
		case GLUT_KEY_UP:
			std::cout << "GLUT_KEY_UP " << camerapositionX << ", " << camerapositionZ << std::endl;
			moveCameraKeyboard(CAMERASPEED,UP);
			break;
		case GLUT_KEY_RIGHT:
			std::cout << "GLUT_KEY_RIGHT " << camerapositionX << ", " << camerapositionZ << std::endl;
			moveCameraKeyboard(CAMERASPEED,RIGHT);
			break;
		case GLUT_KEY_DOWN:
			std::cout << "GLUT_KEY_DOWN " << camerapositionX << ", " << camerapositionZ << std::endl;
			moveCameraKeyboard(-CAMERASPEED,DOWN);
			break;
		case GLUT_KEY_PAGE_UP:
			camerapositionY += (0.1f*CAMERASPEED);
			break;
		case GLUT_KEY_PAGE_DOWN:
			camerapositionY -= (0.1f*CAMERASPEED); 
			break;
		case GLUT_KEY_F1:
			// drohne 1
			if (x1 <= -4.0 && y_first_drone < 4.0) {
				y_first_drone += SPEEDOBJECT;
			}
			else if (x1 < 4.0 && y_first_drone >= 4.0) {
				x1 += SPEEDOBJECT;
			}
			else if (x1 >= 4.0 && y_first_drone > 0.0) {
				y_first_drone -= SPEEDOBJECT;
			}
			else if (x1 >= -4.0 && y_first_drone <= 0.0) {
				x1 -= SPEEDOBJECT;
			}

			// drohne 2
			if (x2 >= 4.0 && y2 > 0.0) {
				y2 -= SPEEDOBJECT;
			}
			else if (x2 >= -4.0 && y2 <= 0.0) {
				x2 -= SPEEDOBJECT;
			}
			else if (x2 <= -4.0 && y2 < 4.0) {
				y2 += SPEEDOBJECT;
			}
			else if (x2 < 4.0 && y2 >= 4.0) {
				x2 += SPEEDOBJECT;
			}
			break;
		default:
			break;
		}
	// RenderScene aufrufen.
	glutPostRedisplay();
}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void drawGrid()
{

	for (float i = -500; i <= 500; i += 5)
	{
		glBegin(GL_LINES);
		glColor3ub(150, 190, 150);
		glVertex3f(-500, 0, i);
		glVertex3f(500, 0, i);
		glVertex3f(i, 0, -500);
		glVertex3f(i, 0, 500);
		glEnd();
	}
}

void moveCameraKeyboard(float speed , direction direction) {

	GLfloat tmpx = cameraTargetX - camerapositionX;
	GLfloat tmpz = cameraTargetZ - camerapositionZ;
	GLfloat tmpy = cameraTargetY - camerapositionY;
	switch (direction) {
	
	case LEFT:
	case RIGHT:{
		break;
		camerapositionX += tmpx*speed;
		cameraTargetX += tmpx*speed;
		break; }
	case UP:
	case DOWN:{
		
		camerapositionX += tmpx * speed;
		camerapositionY += tmpy * speed;
		cameraTargetX += tmpx * speed;
		cameraTargetY += tmpy * speed;
		camerapositionZ += tmpz * speed;
		cameraTargetZ += tmpz * speed;
		break; }
	default:break;
	}

}