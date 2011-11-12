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

typedef enum {
	CONTEXT_MENU_EXIT,
	CONTEXT_MENU_QUAD_STRIP,
	CONTEXT_MENU_VERTEX_ARRAY,
	CONTEXT_MENU_DISPLAY_LIST
} CONTEXT_MENU;

string WINDOW_TITLE = "Using: QUAD, VERTEX, NO_LIST";

GLuint FUNC_DLIST = 0;
const int GRID_SIZE = 256;
GLfloat GRID[GRID_SIZE + 1][GRID_SIZE + 1][3];
GLfloat GRID_VERTICES[(GRID_SIZE + 1) * (GRID_SIZE + 1) * 3];
GLuint GRID_INDICES[(GRID_SIZE + 1) * (GRID_SIZE + 1) * 4];

void calcFunction()
/////////////////////////////////////////////////////////////////////////////////////////
{
	int index = 0;
	int ix, iy;
	float x, y;

	// calculate function value for grid

	for (ix = 0; ix < GRID_SIZE + 1; ix++) {
		for (iy = 0; iy < GRID_SIZE + 1; iy++) {

			GRID[ix][iy][0] = x = float(ix - (GRID_SIZE / 2));
			GRID[ix][iy][1] = y = float(iy - (GRID_SIZE / 2));

			// function1: z = a*(x^2+y^2) + b
			//GRID[ix][iy][2] = -0.015f * ( (x * x) + (y * y) ) + 50.0f ;

			// function2:  z = 1/(1+x^2+y^2)
			//GRID[ix][iy][2] = 75.0f / ( 1.0f + 0.005f * (x * x) +  0.005f * (y * y));

			// function3:  z = a*sin(b*sqrt(x^2+y^2))
			//GRID[ix][iy][2] = 8.0f * sin( 0.3f * sqrt((x * x) + (y * y)) );

			//flat
			GRID[ix][iy][2] = 1.0;

			GRID_VERTICES[index] = x;
			index++;
			GRID_VERTICES[index] = y;
			index++;
			GRID_VERTICES[index] = GRID[ix][iy][2];
			index++;
		}
	}
}

void drawFunction()
/////////////////////////////////////////////////////////////////////////////////////////
{
	int ix, iy;
	int index = 0;
	if (USE_VERTEX_ARRAY) {
		if (USE_QUAD_STRIPS) {

			for (ix = 0; ix < GRID_SIZE; ix++) {
				for (iy = 0; iy < GRID_SIZE + 1; iy++) {
					GRID_INDICES[index] = (ix * (GRID_SIZE + 1)) + iy;
					index++;
					GRID_INDICES[index] = ((ix + 1) * (GRID_SIZE + 1)) + iy;
					index++;
				}
				glDrawElements(GL_QUAD_STRIP, index, GL_UNSIGNED_INT,
						&GRID_INDICES);
				index = 0;
			}

		} else {
			for (ix = 0; ix < GRID_SIZE; ix++) {
				for (iy = 0; iy < GRID_SIZE; iy++) {
					GRID_INDICES[index] = ix * (GRID_SIZE + 1) + iy;
					index++;
					GRID_INDICES[index] = (ix + 1) * (GRID_SIZE + 1) + iy;
					index++;
					GRID_INDICES[index] = (ix + 1) * (GRID_SIZE + 1) + (iy + 1);
					index++;
					GRID_INDICES[index] = ix * (GRID_SIZE + 1) + (iy + 1);
					index++;
				}
			}

			glDrawElements(GL_QUADS, index, GL_UNSIGNED_INT, &GRID_INDICES);

		}

	} else {
		if (USE_QUAD_STRIPS) {

			for (ix = 0; ix < GRID_SIZE; ix++) {
				glBegin(GL_QUAD_STRIP);
				for (iy = 0; iy < GRID_SIZE + 1; iy++) {
					glVertex3f(GRID[ix][iy][0], GRID[ix][iy][1],
							GRID[ix][iy][2]);
					glVertex3f(GRID[ix + 1][iy][0], GRID[ix + 1][iy][1],
							GRID[ix + 1][iy][2]);
				}
				glEnd();
			}

		} else {
			// create grid function surface plot
			for (ix = 0; ix < GRID_SIZE; ix++) {
				for (iy = 0; iy < GRID_SIZE; iy++) {
					glBegin(GL_QUADS);
					glVertex3f(GRID[ix][iy][0], GRID[ix][iy][1],
							GRID[ix][iy][2]);
					glVertex3f(GRID[ix + 1][iy][0], GRID[ix + 1][iy][1],
							GRID[ix + 1][iy][2]);
					glVertex3f(GRID[ix + 1][iy + 1][0], GRID[ix + 1][iy + 1][1],
							GRID[ix + 1][iy + 1][2]);
					glVertex3f(GRID[ix][iy + 1][0], GRID[ix][iy + 1][1],
							GRID[ix][iy + 1][2]);
					glEnd();
				}
			}
		}

	}

}

void display()
/////////////////////////////////////////////////////////////////////////////////////////
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	if (USE_DISPLAY_LIST) {
        glCallList(FUNC_DLIST);
	} else {
		drawFunction();
	}
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
	glClearColor(0.25f, 0.25f, 0.5f, 1.0f);

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
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (GLfloat) w / (GLfloat) h, 1.0, 256.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -128.0);
}

void keyboard(unsigned char key, int x, int y)
/////////////////////////////////////////////////////////////////////////////////////////
		{
	switch (key) {

	case 27: {
		exit(0);
		break;
	}
	}
}

void contextMenu(int i) {
	switch (i) {
	case CONTEXT_MENU_EXIT:
		exit(0);
		break;
	case CONTEXT_MENU_QUAD_STRIP:
		USE_QUAD_STRIPS = !USE_QUAD_STRIPS;
		break;
	case CONTEXT_MENU_VERTEX_ARRAY:
		USE_VERTEX_ARRAY = !USE_VERTEX_ARRAY;
		if (USE_VERTEX_ARRAY) {
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, GRID_VERTICES);
		} else {
			glDisableClientState(GL_VERTEX_ARRAY);
		}

		break;
	case CONTEXT_MENU_DISPLAY_LIST:
		USE_DISPLAY_LIST = !USE_DISPLAY_LIST;
		if (USE_DISPLAY_LIST) {
			// init display lists
			FUNC_DLIST = glGenLists(1);
			glNewList(FUNC_DLIST, GL_COMPILE);
			drawFunction();
			glEndList();
		} else {
			glDeleteLists(FUNC_DLIST, 1);
			FUNC_DLIST = 0;
		}
		break;
	}

	// compose window title string
	WINDOW_TITLE = "Using: ";
	if (USE_QUAD_STRIPS)
		WINDOW_TITLE += "QUAD_STRIPS, ";
	else
		WINDOW_TITLE += "QUAD, ";

	if (USE_VERTEX_ARRAY)
		WINDOW_TITLE += "VERTEX_ARRAY, ";
	else
		WINDOW_TITLE += "VERTEX, ";

	if (USE_DISPLAY_LIST)
		WINDOW_TITLE += "DISPLAY_LIST ";
	else
		WINDOW_TITLE += "NO_LIST ";

	glutPostRedisplay();
}

void createMenu() {
	// create menu
	glutCreateMenu(contextMenu);
	glutAddMenuEntry("Toggle Quad Strips", CONTEXT_MENU_QUAD_STRIP);
	glutAddMenuEntry("Toggle Vertex Array", CONTEXT_MENU_VERTEX_ARRAY);
	glutAddMenuEntry("Toggle Display List", CONTEXT_MENU_DISPLAY_LIST);

	glutAddMenuEntry("Exit", CONTEXT_MENU_EXIT);

	// attach menu to right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

int main(int argc, char** argv)
/////////////////////////////////////////////////////////////////////////////////////////
		{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Display Lists");
	createMenu();

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
