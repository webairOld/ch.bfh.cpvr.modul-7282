/////////////////////////////////////////////////////////////////////////////////////////
// Assignment: CG-02.03A - Solar System (Ver 2.0)                                      //
/////////////////////////////////////////////////////////////////////////////////////////


#include <GL/glut.h>

#include <iostream>
using namespace std;

#include "zpr.h"

// undefine Microsoft specific keywords
#undef near
#undef far


bool ANIMATION_RUNNING = false;


void checkErrorCode()
/////////////////////////////////////////////////////////////////////////////////////////
{
	GLenum errCode;
	const GLubyte *errString;

	if ((errCode = glGetError()) != GL_NO_ERROR)
	{
		errString = gluErrorString(errCode);
		cout << "OpenGL Error Code: " << errCode << " (" << errString << ")" << endl;
	}
}


void display()
/////////////////////////////////////////////////////////////////////////////////////////
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// draw sun
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(2.0, 30, 20);

	glPopMatrix();

	glutSwapBuffers();

	checkErrorCode();
}


void initRendering()
/////////////////////////////////////////////////////////////////////////////////////////
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}



void Menu1(int item)
/////////////////////////////////////////////////////////////////////////////////////////
{
	switch (item)
	{
		case 0:
		{
			exit(0);
			break;
		}
		case 1:
		{
			glutChangeToMenuEntry(1, "Stop Animation", 2);
			ANIMATION_RUNNING = true;
			break;
		}
		case 2:
		{
			glutChangeToMenuEntry(1, "Start Animation", 1);
			ANIMATION_RUNNING = false;
			break;
		}
		default:
		{
			// reset settings
		}
	}
	glutPostRedisplay();
}



void initMenu()
/////////////////////////////////////////////////////////////////////////////////////////
{
    // create menu
    glutCreateMenu(Menu1);
    glutAddMenuEntry("Start Animation", 1);
    glutAddMenuEntry("Exit", 0);

    // attach menu to right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
        case ' ':
		{
			if (ANIMATION_RUNNING)
			{
				Menu1(2);
			} else {
				Menu1(1);
			}
			break;
		}
    }
}



int main(int argc, char *argv[])
/////////////////////////////////////////////////////////////////////////////////////////
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Solar System");
    initRendering();
    initMenu();
	zprInit();

	// register callbacks
    glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
