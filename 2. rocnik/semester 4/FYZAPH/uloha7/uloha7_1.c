#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

const float Lmax = 400.0; // rozmer sceny v smere X
const float fovY = 30;

char title[] = "McLovin";
 
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
   glClearDepth(1.0f);                   
   glEnable(GL_DEPTH_TEST);   
   glDepthFunc(GL_LEQUAL);    
   glShadeModel(GL_SMOOTH);   
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
}
 
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   glMatrixMode(GL_MODELVIEW);     
 
   glLoadIdentity();                 
   glTranslatef(1.5f, 0.0f, -7.0f);
   glColor3f(1.0, 0.0, 0.0);
   	glBegin(GL_LINES);
		glVertex3f(-5,-0.5, -0.1);
		glVertex3f(5,-0.1, -0.5);
	glEnd();  
   
   
   glLoadIdentity();
   glTranslatef(-1.5f, 0.0f, -4.0f);
   
   glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(-5,-0.5, -0.1);
		glVertex3f(5,-0.1, -0.5);
	glEnd();   
 
   glutSwapBuffers();  
}
 
void reshape(GLsizei width, GLsizei height) {  
   if (height == 0) height = 1;                
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   glViewport(0, 0, width, height);
 
   glMatrixMode(GL_PROJECTION);  
   glLoadIdentity();             
   //gluPerspective(fovY, aspect, 0.1f, 100.0f);
   glOrtho(-5.0, 5, -5.0, 5, 0.1f, 100.0f);
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);           
   glutInitDisplayMode(GLUT_DOUBLE); 
   glutInitWindowSize(640, 480);   
   glutInitWindowPosition(50, 50); 
   glutCreateWindow(title);          
   glutDisplayFunc(display);       
   glutReshapeFunc(reshape);       
   initGL();                       
   glutMainLoop();                 
   return 0;
}


