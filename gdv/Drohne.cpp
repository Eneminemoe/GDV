//#include "GL/freeglut.h"
#include "Wuerfel.h"
#include "Drohne.h"
 
void Drohne(GLfloat rotation) {
    glPushMatrix(); {       
        // 1. Flügel
        glPushMatrix(); {
            glRotatef(45.0, 0.0, 1.0, 0.0);
            
            glPushMatrix();
            glTranslatef(1.25, 0.0, -0.0);          
            glScalef(1.5, 0.1, 0.1);
            Wuerfel(1.0, 1.0, 0.4980, 0.1411, 1.0);   // ARM
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(1.9, 0.05, -0.0);    
            glScalef(0.05, 0.075, 0.05);
            Wuerfel(1.0, 0.8039, 0.4, 0.1137, 1.0);   // STEIN
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(1.9, 0.0875, -0.0);  
            glRotatef(rotation, 0.0, 1.0, 0.0);
            glScalef(1.0, 0.01, 0.02);
            Wuerfel(1.0, 1.0, 0.0, 1.0, 1.0);   // ROTORBLATT
            glPopMatrix();
        } glPopMatrix();
        
        // 2. Flügel
        glPushMatrix(); {
            glRotatef(225.0, 0.0, 1.0, 0.0);
            
            glPushMatrix();
            glTranslatef(1.25, 0.0, -0.0);          
            glScalef(1.5, 0.1, 0.1);
            Wuerfel(1.0, 1.0, 0.4980, 0.1411, 1.0);   // ARM
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(1.9, 0.05, -0.0);    
            glScalef(0.05, 0.075, 0.05);
            Wuerfel(1.0, 0.8039, 0.4, 0.1137, 1.0);   // STEIN
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(1.9, 0.0875, -0.0);  
            glRotatef(rotation, 0.0, 1.0, 0.0);
            glScalef(1.0, 0.01, 0.02);
            Wuerfel(1.0, 1.0, 0.0, 1.0, 1.0);   // ROTORBLATT
            glPopMatrix();
        } glPopMatrix();
        
        // 3. Flügel
        glPushMatrix(); {
            glRotatef(135.0, 0.0, 1.0, 0.0);
            
            glPushMatrix();
            glTranslatef(1.25, 0.0, -0.0);          
            glScalef(1.5, 0.1, 0.1);
            Wuerfel(1.0, 1.0, 0.4980, 0.1411, 1.0);   // ARM
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(1.9, 0.05, -0.0);    
            glScalef(0.05, 0.075, 0.05);
            Wuerfel(1.0, 0.8039, 0.4, 0.1137, 1.0);   // STEIN
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(1.9, 0.0875, -0.0);  
            glRotatef(rotation, 0.0, 1.0, 0.0);
            glScalef(1.0, 0.01, 0.02);
            Wuerfel(1.0, 1.0, 0.0, 1.0, 1.0);   // ROTORBLATT
            glPopMatrix();
        } glPopMatrix();
        
        // 4. Flügel
        glPushMatrix(); {
            glRotatef(315.0, 0.0, 1.0, 0.0);
            
            glPushMatrix();
            glTranslatef(1.25, 0.0, -0.0);          
            glScalef(1.5, 0.1, 0.1);
            Wuerfel(1.0, 1.0, 0.4980, 0.1411, 1.0);   // ARM
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(1.9, 0.05, -0.0);    
            glScalef(0.05, 0.075, 0.05);
            Wuerfel(1.0, 0.8039, 0.4, 0.1137, 1.0);   // STEIN
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(1.9, 0.0875, -0.0);  
            glRotatef(rotation, 0.0, 1.0, 0.0);
            glScalef(1.0, 0.01, 0.02);
            Wuerfel(1.0, 1.0, 0.0, 1.0, 1.0);   // ROTORBLATT
            glPopMatrix();
        } glPopMatrix();
        
        glPushMatrix();
        glScalef(1.0, 0.11, 1.0);
        Wuerfel(1.0, 0.4117, 0.4117, 0.4117, 1.0);   // KÖRPER
        glPopMatrix();
       
    } glPopMatrix();
}