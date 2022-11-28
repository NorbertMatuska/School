#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265

const float icaskrok = 25;

const float Lmax = 400.0; // rozmer sceny v smere X

float v = 0.0; //rychlost
float g = 9.80665;
const float dt = 0.01;
float t = 0.0;
float h0 = 10.0;
float y = 0;
int alfa = 0;
float val = PI / 180;
float v1 = 0;
float x, y, vx, vy;

/*const int steps = 100;
const float angle = 3.1415926 * 2.0 / steps;
float xPos = 0; float yPos = 0; float radius = 1.0;
float prevX = 0.0;
float prevY = 0.0;
*/
FILE *subor;

void aktualizuj(const int ihod)
{
	glutPostRedisplay();
	glutTimerFunc(icaskrok, aktualizuj, ihod+1);
	
	t += dt;
	vx = v1*cos(alfa*val);
	vy = v1 - g*t;
	x = -0.16*Lmax+(vx*cos(alfa*val))*t;
	y = 0.09*Lmax+((vy*sin(alfa*val))*t)-0.5*(g*(t*t));
	v = sqrt((vx*vx)+(vy*vy));
	fprintf(subor,"%f %f %f %f %f %f\n", t, x, y, vx, vy, v);
	
	if (y <= -0.1*Lmax) {
		printf("Koniec programu\n");
		exit(0);
	}
	
}

void obsluhaResize (int sirka , int vyska )
{
	glViewport (0, 0, sirka , vyska );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	if ( sirka == 0) sirka ++;
	const float pomstr = ((float) vyska )/ sirka ;
	//gluOrtho2D ( -0.5* Lmax , 0.5* Lmax , -0.5* Lmax * pomstr , 0.5* Lmax * pomstr );
	float mat[16];
	for(int ii=0; ii<16; ii++)
	{
		mat[ii] = 0.0;
	}
	mat[0] = 2.0/Lmax;
	mat[5] = 2.0/(Lmax*pomstr);
	mat[10] = 1.0;
	mat[15] = 1.0;
	
	glLoadMatrixf(mat);
}
void kresliObdlznik2D ()
{
	glClear ( GL_COLOR_BUFFER_BIT );
	glColor3f (0.0 , 1.0 , 1.0);
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity();
	glScalef(2.0, 2.0, 1.0);
	//glTranslatef(-50.0, 0.0, 0.0);
	
	glBegin (GL_QUADS);
		glVertex2f( -0.2*Lmax , -0.1*Lmax);
		glVertex2f( -0.16*Lmax, -0.1*Lmax);
		glVertex2f( -0.16*Lmax, 0.1*Lmax);
		glVertex2f( -0.2*Lmax, 0.1*Lmax);
	glEnd ();
	
	//glTranslatef(-25.0, 20.0, 0.0);
	glColor3f(128.0, 0.0, 128.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(-0.2*Lmax, 0.1*Lmax);
		glVertex2f(-0.16*Lmax,0.1*Lmax);
		glVertex2f(-0.18*Lmax,0.15*Lmax);
	glEnd();
	
	
	
	/*for (int i = 0; i <= radius; i++) {
		float newX = radius * sin(angle * i);
		float newY = -radius * cos(angle * i);
		glBegin(GL_TRIANGLES);
			glColor3f(0.0,0.5,0.0);
			glVertex2f(0.0*Lmax, 0.0*Lmax);
			glVertex2f(prevX*Lmax, prevY*Lmax);
			glVertex2f(newX*Lmax, newY*Lmax);
		glEnd();
		prevX = newX;
		prevY = newY;
			
	}*/
	glPointSize(20.0);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(128,128,128);
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();
	
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(-Lmax,-0.1*Lmax);
		glVertex2f(Lmax,-0.1*Lmax);
	glEnd();
	glutSwapBuffers ();
}

int main (int argc , char ** argv )
{
	subor = fopen("sikmyvrh.txt", "w");
	if (subor == NULL) {
		printf("error\n");
		exit(1);
	}
	printf("Zadajte uhol alpha:\n");
	scanf(" %d", &alfa);
	printf("Zadajte rychlost v interval 1-64\n");
	scanf(" %f", &v1);
	fprintf(subor, "# t=0s alpha = %d v = %f\n", alfa, v);
	
	glutInit (& argc , argv );
	glutInitDisplayMode ( GLUT_DOUBLE );
	glutInitWindowSize (900 , 640); // zvolme nateraz stvorcove okno
	glutInitWindowPosition (150 , 150);
	glutCreateWindow (" majkl dzeksn ");
	glutDisplayFunc ( kresliObdlznik2D );
	glClearColor (0.8 , 0.3 , 0.3 , 0.3);
	// Zavedieme ,callback' funkciu obsluhaResize().
	glutReshapeFunc ( obsluhaResize );
	glutTimerFunc(icaskrok, aktualizuj, 0);
	glutMainLoop ();
	return 0;
}
