/////////////////////////////////////////////////////////////////////////////////////////
// Assignment: CG-02.03A - Solar System (Ver 2.0)                                      //
/////////////////////////////////////////////////////////////////////////////////////////


#include <GL/glut.h>
#include <math.h>

#include <iostream>
using namespace std;

#include "zpr.h"

// undefine Microsoft specific keywords
#undef near
#undef far


bool ANIMATION_RUNNING = false;

int SPEED = 20;

float ANGLE_1 = 0.0f;


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

void calculateAnimations (int timerId) {
	ANGLE_1 += 2.0f;
	ANGLE_1 = fmod(ANGLE_1,360.0f);
	glutPostRedisplay();
	if (ANIMATION_RUNNING) {
		glutTimerFunc(SPEED,calculateAnimations,0);
	}


}

void display()
/////////////////////////////////////////////////////////////////////////////////////////
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

	// draw sun

    glPushMatrix();
    glRotatef(ANGLE_1,0.0f,0.0f,1.0f);
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
			glutTimerFunc(10,calculateAnimations,0);
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
        case '+':
        {
        	SPEED = (SPEED > 1) ? SPEED-1 : 1;
        	cout << "new Speed: "<< SPEED << endl;
        	break;
        }
        case '-':
        {

        	SPEED += 1;
        	cout << "new Speed: "<< SPEED << endl;
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
