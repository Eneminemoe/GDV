// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include "GL/freeglut.h"         //lädt alles für OpenGL
#include "Wuerfel.h"
#include "Drohne.h"

GLfloat fRotation = 0.0;
GLfloat rotorDegree = 10.0;
GLfloat x1 = -4.0, y1=0.0;
//GLfloat y1 = 0.0;
GLfloat x2 = 4.0;
GLfloat y2 = 4.0;

void Init()	
{
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
   // durchgeführt werden müssen
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
}

void RenderScene() //Zeichenfunktion
{
    // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
    glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
    // (Kameraposition / Blickpunkt / Up-Vektor)
    gluLookAt ( 0.0, 3.0, 7.0, 0., 2., 0., 0., 1., 0.);
    // "blauer Himmel"
    glClearColor( 0.52941, 0.80784, 0.92156, 1.0 );  
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // glutWireCube(0.2);
    
    // Boden einzeichnen
    glBegin(GL_POLYGON);
    glColor4f(0.00392, 0.65098, 0.06666, 1.0);
    glVertex3f(-100.0, 0.0, -100.0);
    glVertex3f(-100.0, 0.0, 100.0);
    glVertex3f(100.0, 0.0, 100.0);
    glVertex3f(100.0, 0.0, -100.0);
    glEnd();

    glPushMatrix();
        glTranslatef(x1, y1, 0.0);
        Drohne(fRotation);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(x2, y2, 0.0);
        Drohne(fRotation);
    glPopMatrix();
    
    glutSwapBuffers();
}

void Reshape(int width,int height)
{
    // Hier finden die Reaktionen auf eine Veränderung der Größe des 
    // Graphikfensters statt
    
    // Matrix für Transformation: Frustum->viewport
    glMatrixMode(GL_PROJECTION);
    // Aktuelle Transformations-Matrix zuruecksetzen
    glLoadIdentity ();
    // Viewport definieren
    glViewport(0,0,width,height);
    // Frustum definieren (siehe unten)
    // glOrtho( -1., 1., -1., 1., 0.0, 2.0);
    // gluPerspective(senkr. Oeffnungsw., Seitenverh., zNear, zFar);
    gluPerspective(120., 1., 0.1, 20.0);
    // Matrix für Modellierung/Viewing
    glMatrixMode(GL_MODELVIEW);
}

void Animate (int value)    
{
   // Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
   // erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
   // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
   // inkrementiert und dem Callback wieder uebergeben. 
   // std::cout << "value=" << value << std::endl;
   
   // Rotorblätter drehen
   fRotation = fRotation - rotorDegree; // Rotationswinkel aendern
   if (fRotation <= 0.0) {
       fRotation = fRotation + 360.0;
   }
   
   GLfloat speed = 0.015625;   // 0.125, 0.015625, 0.0625
   
   
   /* Flugkurve
    
    -4/4 --------- 4/4 
    |               |
    |               |
    |               |
    |               |
    -4/0 --------- 4/0
    
    */
   
   // drohne 1
   if ( x1 == -4.0 && y1 < 4.0 ) {
       y1 += speed;
   }
   else if ( x1 < 4.0 && y1 == 4.0 ) {
       x1 += speed;
   }
   else if ( x1 == 4.0 && y1 > 0.0 ) {
       y1 -= speed;
   }
   else if ( x1 > -4.0 && y1 == 0.0 ) {
       x1 -= speed;
   }
   // drohne 2
   if ( x2 == 4.0 && y2 > 0.0 ) {
       y2 -= speed;
   }
   else if ( x2 > -4.0 && y2 == 0.0 ) {
       x2 -= speed;
   }
   else if ( x2 == -4.0 && y2 < 4.0 ) {
       y2 += speed;
   }
   else if ( x2 < 4.0 && y2 == 4.0 ) {
       x2 += speed;
   }
   // debug
   std::cout << "x1 = " << x1 << std::endl;
   std::cout << "y1 = " << y1 << std::endl;
   std::cout << std::endl;
   std::cout << "x2 = " << x2 << std::endl;
   std::cout << "y2 = " << y2 << std::endl;
   std::cout << "---" << std::endl;
   
   
   // RenderScene aufrufen
   glutPostRedisplay();
   // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
   int wait_msec = 10;
   glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char **argv)
{
   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize( 600, 600 );         // Fenster-Konfiguration
   glutCreateWindow( "GDV" );   // Fenster-Erzeugung
   glutDisplayFunc( RenderScene );         // Zeichenfunktion bekannt machen
   glutReshapeFunc( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, Animate, 0);
   Init();
   glutMainLoop();
   return 0;
}