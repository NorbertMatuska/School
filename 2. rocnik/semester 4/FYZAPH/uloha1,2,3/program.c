#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

const unsigned icaskrok = 25;
const float Lmax = 15.0; //rozmer sceny v smere X
float posunX = 0.0;

void aktualizuj2(const int ihod);

void aktualizuj(const int ihod) {
	posunX += 0.05;
	glutPostRedisplay();
	if (posunX >= 0.5 * Lmax){
		glutTimerFunc(icaskrok, aktualizuj2, 0);
	}
	else {
	glutTimerFunc(icaskrok, aktualizuj,ihod+1);
	//printf("cas: %lf", posunX);
	}
}
void aktualizuj2(const int ihod) {
	posunX -= 0.05;
	glutPostRedisplay();
	if (posunX <= -0.5 * Lmax) {
		glutTimerFunc(icaskrok, aktualizuj, 0);
	}
	else {
	glutTimerFunc(icaskrok, aktualizuj2,ihod+1);
	//printf("cas: %lf", posunX);
	}
}

void obsluhaResize(int width, int height){
	glViewport(0,0,width, height);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	if (width == 0) width++;
	const float sideRatio = ((float)height/width);
	//gluOrtho2D(-0.5*Lmax, 0.5*Lmax, -0.5*Lmax*sideRatio, 0.5*Lmax*sideRatio);
	float mat[16];
	for(int ii=0; ii<16; ii++) {
		mat[ii] = 0.0;
	}
	mat[0] = 2.0/Lmax;
   	mat[5] = 2.0/(Lmax*sideRatio);
   	mat[10] = 1.0;
   	mat[15] = 1.0;

   	glLoadMatrixf(mat);
}


void draw_triangle(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);

	// gluOrtho2D(-2.0, 2.0, -1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1.0, 1.0, 1.0);
	glTranslatef(posunX, 0.0, 0.0);

	glBegin(GL_TRIANGLES);
		glVertex2f(-0.1*Lmax,-0.1*Lmax);
		glVertex2f(0.1*Lmax,-0.1*Lmax);
		glVertex2f(0*Lmax,0.1*Lmax);
	glEnd();

	glutSwapBuffers();

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(150,150);
	glutCreateWindow("unsuspecting window");
	glutDisplayFunc(draw_triangle);
	glClearColor(1,0,1,1);
	glutReshapeFunc(obsluhaResize);
	glutTimerFunc(icaskrok, aktualizuj, 0);
	glutMainLoop();

return 0;
}
