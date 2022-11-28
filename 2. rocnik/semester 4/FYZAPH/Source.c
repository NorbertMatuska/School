#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <gl/GL.h>

int once = 1;
const int icaskrok = 25;
float posunX = 0.0f;
float posun2X = 0.0f;
int Lmax = 700;


// netuöil som ako to spraviù (Ëiûe inöpirovanÈ internetom)
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w,
			1.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
	else
		glOrtho(-1.0 * (GLfloat)w / (GLfloat)h,
			1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void aktualizuj(const int ihod)
{
	// obdlznik
	posunX += 0.015;
	// trojuholnik
	posun2X += 0.005;

	glutPostRedisplay();
	glutTimerFunc(icaskrok, aktualizuj, ihod);
}

void DisplayFunc()
{
	glClearColor(0.7, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(-1, 0, 0);

	// obdlznik
	glBegin(GL_QUADS);
	glColor3ub(102, 0, 102);
	glVertex2f(-0.3f + posunX, -0.15f);

	glColor3ub(50, 0, 50);
	glVertex2f(0.3f + posunX, -0.15f);

	glColor3ub(200, 0, 200);
	glVertex2f(0.3f + posunX, 0.15f);

	glColor3ub(0, 0, 0);
	glVertex2f(-0.3f + posunX, 0.15f);
	glEnd();

	// trojuholnik
	glTranslatef(1, 0, 0);

	glBegin(GL_TRIANGLES);
	glColor3ub(50, 20, 102);
	glVertex2f(0 + posun2X, 0.3f);

	glColor3ub(10, 0, 50);
	glVertex2f(0.3f + posun2X, -0.15);

	glColor3ub(20, 124, 200);
	glVertex2f(-0.3f + posun2X, -0.15);
	glEnd();

	glutSwapBuffers();
}

int vypocet_rychlosti(float rychlost)
{
	// cas je 25ms  
	// rychlost posun 0,015km-obdlznik 0,005km-trojuholnik 
	// rychlosù do km -> * 1000
	// vzdialenost Lmax 700m
	// vypoËet 25*40 = 1s -> za 1s trojuholnik prejde 0,02m a obdlznik 0,03m
	// jedna min * 60
	// hod -> * 60
	return ((((rychlost) * 40) * 60) * 60);
}

int main(int argc, char** argv)
{
													// trojuhonik zaËÌna v polke
	printf("Trojuholni ide rychlostou: %dkm/h.\n", vypocet_rychlosti(0.005));
	printf("Obdlznik ide rychlostou: %dkm/h.", vypocet_rychlosti(0.015));
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(Lmax, 700);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("Shape");
	glutReshapeFunc(resize);
	glutDisplayFunc(DisplayFunc);
	glutTimerFunc(icaskrok, aktualizuj, 0);
	glutMainLoop();

	return 0;
}