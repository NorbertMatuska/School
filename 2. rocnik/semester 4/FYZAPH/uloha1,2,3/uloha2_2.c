#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

const float icaskrok = 10;

const float Lmax = 400.0; // rozmer sceny v smere X

float posunX = 0.0;
float v = 0.0; //rychlost
FILE *subor;

void aktualizuj(const int ihod)
{
	posunX += v;
	glutPostRedisplay();
	glutTimerFunc(icaskrok, aktualizuj, ihod+1);
	//printf("cas: %d ms\n", ihod*10);
	fprintf(subor, "%d %f\n", ihod*10, posunX);
	if (posunX >= 100) {
		printf("koniec programu\n");
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
	glTranslatef(posunX, 0.0, 0.0);
	
	glBegin (GL_QUADS);
		glVertex2f( -0.01*Lmax , -0.01*Lmax);
		glVertex2f( 0.01*Lmax, -0.01*Lmax);
		glVertex2f( 0.01*Lmax, 0.01*Lmax);
		glVertex2f( -0.01*Lmax, 0.01*Lmax);
	glEnd ();
	glutSwapBuffers ();
}
int main (int argc , char ** argv )
{
	subor = fopen("data.txt", "w");
	if (subor == NULL) {
		printf("error\n");
		exit(1);
	}
	printf("zadajte zaciatocnu suradnicu x0:\n");
	scanf(" %f", &posunX);
	printf("zadajte rychlost v:\n");
	scanf(" %f", &v);
	
	glutInit (& argc , argv );
	glutInitDisplayMode ( GLUT_DOUBLE );
	glutInitWindowSize (900 , 640); // zvolme nateraz stvorcove okno
	glutInitWindowPosition (150 , 150);
	glutCreateWindow (" OpenGL : obdlznik ");
	glutDisplayFunc ( kresliObdlznik2D );
	glClearColor (0.8 , 0.3 , 0.3 , 0.3);
	// Zavedieme ,callback' funkciu obsluhaResize().
	glutReshapeFunc ( obsluhaResize );
	glutTimerFunc(icaskrok, aktualizuj, 0);
	glutMainLoop ();
	return 0;
}
