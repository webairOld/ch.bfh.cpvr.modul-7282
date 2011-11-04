/////////////////////////////////////////////////////////////////////////////////////////
// Assignment: CG-02-02A - Function Plotter (Ver 2.0)                                  //
/////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

#include "zpr.h"
#include "UtilGlut.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

bool USE_QUAD_STRIPS = false;
bool USE_VERTEX_ARRAY = false;
bool USE_DISPLAY_LIST = false;
string WINDOW_TITLE = "Using: QUAD, VERTEX, NO_LIST";

GLuint FUNC_DLIST = 0;
const int GRID_SIZE = 128;
GLfloat GRID[GRID_SIZE + 1][GRID_SIZE + 1][3];




void calcFunction()
/////////////////////////////////////////////////////////////////////////////////////////
{
	int index = 0;
    int ix, iy;
	float x, y;

	// calculate function value for grid
	for (ix = 0; ix < GRID_SIZE+1; ix++)
    {
		for (iy = 0; iy < GRID_SIZE+1; iy++)
		{

			GRID[ix][iy][0] = x = float(ix - (GRID_SIZE/2));
			GRID[ix][iy][1] = y = float(iy - (GRID_SIZE/2));

			// function1: z = a*(x^2+y^2) + b
			//GRID[ix][iy][2] = -0.015f * ( (x * x) + (y * y) ) + 50.0f ;

			// function2:  z = 1/(1+x^2+y^2)
			//GRID[ix][iy][2] = 75.0f / ( 1.0f + 0.005f * (x * x) +  0.005f * (y * y));

			// function3:  z = a*sin(b*sqrt(x^2+y^2))
			//GRID[ix][iy][2] = 8.0f * sin( 0.3f * sqrt((x * x) + (y * y)) );
		}
    }
}



void drawFunction()
/////////////////////////////////////////////////////////////////////////////////////////
{
	int ix, iy;
	int index = 0;

	// create grid function surface plot 
	for (ix = 0; ix < GRID_SIZE; ix++)
	{
		for (iy = 0; iy < GRID_SIZE; iy++)
		{  
			glBegin(GL_QUADS);
			glVertex3f(GRID[ix][iy][0], GRID[ix][iy][1], GRID[ix][iy][2]);
			glVertex3f(GRID[ix+1][iy][0], GRID[ix+1][iy][1], GRID[ix+1][iy][2]);
			glVertex3f(GRID[ix+1][iy+1][0], GRID[ix+1][iy+1][1], GRID[ix+1][iy+1][2]);
			glVertex3f(GRID[ix][iy+1][0], GRID[ix][iy+1][1], GRID[ix][iy+1][2]);
			glEnd();
		}
	}
}



void display()
/////////////////////////////////////////////////////////////////////////////////////////
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		drawFunction();
	glPopMatrix();

	glutSwapBuffers();
	UtilGlut::showFPS(WINDOW_TITLE);
	UtilGlut::showErrorCode();
}



void initRendering()
/////////////////////////////////////////////////////////////////////////////////////////
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set background color
	glClearColor( 0.25f, 0.25f, 0.5f, 1.0f );

	// set foreground color
	glColor3f(1.0F, 0.9F, 0.1F);

    // general init
    glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}



void resize(int w, int h)
/////////////////////////////////////////////////////////////////////////////////////////
{
	glViewport(0, 0, (GLsizei) w , (GLsizei) h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(75.0, (GLfloat) w/(GLfloat) h, 1.0, 256.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glTranslatef(0.0, 0.0, -128.0);
}



void keyboard(unsigned char key, int x, int y)
/////////////////////////////////////////////////////////////////////////////////////////
{
    switch (key)
    {
        case 27:
		{
			exit(0);
			break;
		}
	}
}



int main(int argc, char** argv)
/////////////////////////////////////////////////////////////////////////////////////////
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Display Lists");
    initRendering();
	zprInit();

	// register callbacks
    glutDisplayFunc(display);
    glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
    glutReshapeFunc(resize);

	// calculate grid function values
	calcFunction();

    glutMainLoop();
    return 0;
}
