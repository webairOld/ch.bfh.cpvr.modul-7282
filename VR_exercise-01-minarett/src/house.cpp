/////////////////////////////////////////////////////////////////////////////////////////
// Assignment: CG-02.01A - 3D House (Ver 2.0)                                          //
/////////////////////////////////////////////////////////////////////////////////////////


#include <GL/glut.h>

#include <iostream>
using namespace std;

#include "zpr.h"

const float MINARETT_DIAMETER = 2.0F;     // width of the minarett
const float MINARETT_HEIGHT = 16.0F;    // height of the minarett


void checkErrorCode(void)
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



void drawHouse(float height, float diameter)
/////////////////////////////////////////////////////////////////////////////////////////
{
	// draw ground


	float base = 0.0 - (height/2);
	float towerHeight = (height/2);


	//Fundament
	glColor3f(0.0, 0.75, 0.0);
	//base
	glEnable(GL_NORMALIZE);

    glBegin(GL_QUADS);

    glVertex3f(diameter,base, diameter);
		glVertex3f(diameter,  base, 0.0f);
		glVertex3f(0.0f, base, 0.0f);
		glVertex3f(0.0f, base, diameter);
		glVertex3f(diameter,base, diameter);
    glEnd();

    float sectionHeight = towerHeight - ((height/13) * 2);

	//first section
    glColor3f(1.0F, 0.0F, 0.0F);
    glBegin(GL_QUADS);

	glVertex3f(0.0F, base, 0.0F);
	glVertex3f(diameter,  base, 0.0F);
	glVertex3f(diameter,sectionHeight, 0.0F);
	glVertex3f(0.0F,  sectionHeight, 0.0F);

	glVertex3f(0.0F, base, 0.0F);
	glVertex3f(0.0F,  base, diameter);
	glVertex3f(0.0F,sectionHeight, diameter);
	glVertex3f(0.0F,  sectionHeight, 0.0F);

	glVertex3f(0.0F, base, diameter);
	glVertex3f(diameter,  base, diameter);
	glVertex3f(diameter,sectionHeight, diameter);
	glVertex3f(0.0F,  sectionHeight, diameter);

	glVertex3f(diameter, base, diameter);
	glVertex3f(diameter,  base, 0.0F);
	glVertex3f(diameter,sectionHeight, 0.0F);
	glVertex3f(diameter,  sectionHeight, diameter);

    glEnd();


    //dach

    glColor3f(0.0F, 0.0F, 1.0F);
    glBegin(GL_TRIANGLES);

    glVertex3f((diameter/2),towerHeight,(diameter/2));
    glVertex3f(0.0F,sectionHeight,0.0F);
    glVertex3f(0.0F,sectionHeight,diameter);

    glVertex3f((diameter/2),towerHeight,(diameter/2));
    glVertex3f(0.0F,sectionHeight,diameter);
    glVertex3f(diameter,sectionHeight,diameter);

    glVertex3f((diameter/2),towerHeight,(diameter/2));
    glVertex3f(diameter,sectionHeight,diameter);
    glVertex3f(diameter,sectionHeight,0.0F);

    glVertex3f((diameter/2),towerHeight,(diameter/2));
    glVertex3f(diameter,sectionHeight,0.0F);
    glVertex3f(0.0F,sectionHeight,0.0F);

    glEnd();

    //balkon erster stock ;)


}


void display(void)
/////////////////////////////////////////////////////////////////////////////////////////
{
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT);

	drawHouse(MINARETT_HEIGHT,MINARETT_DIAMETER);
	glFlush();

	glPopMatrix();
	checkErrorCode();
}


void initRendering()
/////////////////////////////////////////////////////////////////////////////////////////
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}


void menu1(int item)
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
			glutSetWindowTitle("3D House (Wireframe Mode)");
			glutChangeToMenuEntry(1, "Disable Wireframe", 2);
			break;
		}
		case 2:
		{
			glutSetWindowTitle("3D House (Solid Mode)");
			glutChangeToMenuEntry(1, "Enable Wireframe", 1);
			break;
		}
		case 3:
		{
			glEnable(GL_CULL_FACE);
			glutChangeToMenuEntry(2, "Disable Culling", 4);
			break;
		}
		case 4:
		{
			glDisable(GL_CULL_FACE);
			glutChangeToMenuEntry(2, "Enable Culling", 3);
			break;
		}
		default:
		{
		}
	}
	glutPostRedisplay();
}



void initMenu()
/////////////////////////////////////////////////////////////////////////////////////////
{
    // create menu
    glutCreateMenu(menu1);
    glutAddMenuEntry("Enable Wireframe", 1);
    glutAddMenuEntry("Enable Culling", 3);
    glutAddMenuEntry("Exit", 0);

    // attach menu to right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char** argv)
/////////////////////////////////////////////////////////////////////////////////////////
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D House");
    initRendering();
    initMenu();
	zprInit();

	// register callbacks
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
