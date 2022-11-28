#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

void resize();
void display_ball();
void update(int time);
void display_func();

const int icaskrok = 0.01 * 1000; // in m/s
float dt = 0.01; // in s

const float gzry= 9.80665;
float time_passed = 0.0;
float ball_x;
float ball_y;
float ball_z;
float v0;
float alpha0;
float theta;
float vy;
float vy0;
float vx;
float vx0;
float vz;
float vz0;
float v;

float zmin;
float zmax;
float xmin;
float xmax;
float ymin;
float ymax;
float z0;

float scene_xmin, scene_xmax, scene_ymax, scene_ymin, scene_zmax, scene_zmin;
float Lx, Ly, Lz;

float flight_time;

FILE *ptr;



int main(int argc, char **argv) {
    
    scanf(" %f", &v0);
    scanf(" %f", &alpha0);
    scanf(" %f", &z0);
    scanf(" %f", &theta);

    vx0 = v0 * cos((M_PI / 180) * alpha0) * cos((M_PI / 180) * theta);
    vy0 = v0 * cos((M_PI / 180) * alpha0) * sin(theta * (M_PI / 180));
    vz0 = v0 * sin((M_PI / 180) * alpha0);

    flight_time = (1 / gzry) * (vz0 + sqrt(pow(vz0, 2) + (2 * gzry * z0)));

    zmin = fminf(0, z0);
    if (vz > 0) {
        zmax = z0;
    } else {
        zmax = z0 + (pow(vz0, 2) / (2 * gzry));
    }

    if (vx0 >= 0) {
        xmin = 0;
        xmax = vx0 * flight_time;
    } else {
        xmax = 0;
        xmin = vx0 * flight_time;
    }

    if (vy0 >= 0) {
        ymin = 0;
        ymax = vy0 * flight_time;
    } else {
        ymax = 0;
        ymin = vy0 * flight_time;
    }

    Lx = xmax - xmin;
    Ly = ymax - ymin;
    Lz = zmax - zmin;

    scene_xmin = xmin - (0.05 * Lx) - (10 * 0.2);
    scene_xmax = xmax + (0.05 * Lx) + (10 * 0.2);

    scene_ymin = ymin - (0.05 * Ly) - (10 * 0.2);
    scene_ymax = ymax + (0.05 * Ly) + (10 * 0.2);

    scene_zmin = zmin - (0.05 * Lz) - (10 * 0.2);
    scene_zmax = zmax + (0.05 * Lz) + (10 * 0.2);

    ptr = fopen("vystup.dat", "w");
    fprintf(ptr, "#value of v0: %f and of angle alpha0: %f and initial height: %f and of angle phi0: %f\n", v0, alpha0, z0, theta);


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(200,150);

    glutCreateWindow("assignment 6 reworked");
    glutDisplayFunc(display_func);

    glClearColor(0,0,0,0);
    glutReshapeFunc(resize);
    glutTimerFunc(icaskrok, update, dt);

    glutMainLoop();

    return 0;
}

void resize(int width, int height) {

    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    if (width == 0)
        width++;

    glOrtho(scene_ymin , scene_ymax, scene_zmin, scene_zmax, -scene_xmax, -scene_xmin);
}

void display_func() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,0);

    // X_AXIS
    glBegin(GL_LINES);
    glVertex3f(scene_ymin,0,0);
    glVertex3f(scene_ymax,0,0);
    glEnd();

    // Y_AXIS
    glBegin(GL_LINES);
    glVertex3f(0,scene_zmin,0);
    glVertex3f(0,scene_zmax,0);
    glEnd();

    // Z_AXIS
    glBegin(GL_LINES);
    glVertex3f(0, 0,-scene_xmax);
    glVertex3f(0, 0,-scene_xmin);
    glEnd();

    display_ball();
    glutSwapBuffers();
}

void display_ball() {
    GLfloat angle;

    glColor3f(0.1,0.1,0.1);
    glBegin(GL_TRIANGLE_FAN);

    for ( angle = 0.0f; angle <= (2.0f * M_PI); angle += 0.01 ) {
        glVertex3f(ball_y + 0.2 * sin(angle), ball_z + 0.2 * cos(angle), ball_x);
    }
    glEnd();
}

void update(int time) {

    vy = vy0;
    vx = vx0;
    vz = vz0 - (gzry * time_passed);

    ball_x = vx0 * time_passed;
    ball_y = vy0 * time_passed;
    ball_z = z0 + (vz0 * time_passed) - (0.5 * gzry * pow(time_passed, 2));
    
	
    //fprintf(ptr, "%f %f %f %f %f %f %f %f\n", time_passed, vx, vy, vz, v, ball_y, ball_z, ball_x);

    //update output file
    ptr = fopen("vystup.dat", "a");
    fprintf(ptr, "%f %f %f %f %f %f %f %f\n", time_passed, vx, vy, vz, v, ball_y, ball_z, ball_x);
    fclose(ptr);

    time_passed += dt;

    if (time_passed > flight_time) {
        dt = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(icaskrok, update, time + 1);
}
