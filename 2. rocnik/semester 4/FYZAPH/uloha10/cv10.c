// hard disk model

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846 // ofc z nejakeho dovodu to nie je definovane
#endif


#include <stdio.h>


typedef struct _OBJSTATUS {
    float x_offset, y_offset;
    float speed, r;
} OBJSTATUS, *POBJSTATUS;


const float DT = 25;
const float G = 9.80665;
const float Lmax = 6.0;
const float Lx = 2.5;
const float Ly = 1.5;

float alpha0 = -0.6;
float vx, vy;

OBJSTATUS point = {0.0, 0.0, 1.4, 0.075};
float t = 0.0;

float ratio = 9.0/16.0;


float rad(float deg) {
    return deg * (M_PI / 180.0);
}

void displ() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glScalef(Lx, Ly, 1.0);
    glRectf(-0.5, -0.5, 0.5, 0.5);

    glPopMatrix();
    

    // circle
    glColor3f(0.5, 0.2, 0.2);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 32; i++)
    {
        float theta = 2.0f * 3.1415926f * (float)i / 32.0;

        float x = point.r * cosf(theta);
        float y = point.r * sinf(theta);

        glVertex2f(x + point.x_offset, y + point.y_offset);

    }
    glEnd();
    glutSwapBuffers();
}

void update(const int idkwhat) {
    if( fabsf(point.y_offset) + point.r >=  Ly * 0.5 ) vy *= -1;
    if( fabsf(point.x_offset) + point.r >=  Lx * 0.5 ) vx *= -1;
    
    point.x_offset += vx * (DT / 1000);
    point.y_offset += vy * (DT / 1000);

    glutPostRedisplay();
    glutTimerFunc(DT, update, idkwhat + 1);
}

void resizeManager_c(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w == 0) w++;

    ratio = (float)h / w;

    gluOrtho2D(-0.5 * Lmax, 0.5 * Lmax, -0.5 * Lmax * ratio, 0.5 * Lmax * ratio);
}


int main (int argc, char *argv[]) {
    /*printf("v0: ");
    scanf("%f", &point.speed);*/
    /*printf("a0: ");
    scanf("%f", &alpha0);*/
    /*printf("x0: ");
    scanf("%f", &point.x_offset);
    printf("y0: ");
    scanf("%f", &point.y_offset);*/

    point.x_offset = 0.3 * Lx;
    point.y_offset = -0.1 * Ly;
    vx = point.speed * cos(alpha0);
    vy = point.speed * sin(alpha0);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowSize(1600, 900);

    glutInitWindowPosition(200, 150);

    glutCreateWindow("Win");

    glClearColor(0, 0, 0, 0);

    glutDisplayFunc(displ);

    glutReshapeFunc(resizeManager_c);


    glutTimerFunc(DT, update, 0);

    glutMainLoop();
    return 0;
}
