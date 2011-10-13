/////////////////////////////////////////////////////////////////////////////////////////
// Assignment: CG-02.01A - 3D House (Ver 2.0)                                          //
/////////////////////////////////////////////////////////////////////////////////////////


#include <GL/glut.h>

#include <iostream>
using namespace std;

#include "zpr.h"

const float HEIGHT = 12.0F;
const float WIDTH = 10.0F;


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



void drawHouse(float height, float width)
/////////////////////////////////////////////////////////////////////////////////////////
{
	// draw ground

	float baseRight = (width/2);
	float baseLeft = 0.0f - (width/2);
	float baseFront = baseRight;
	float baseBack = baseLeft;
	float baseHeight = 0.0f - (height/2);



	//building ground

	glColor3f(0.0, 0.75, 0.0);
    glBegin(GL_QUADS);
    	glVertex3f(baseLeft,baseHeight,baseBack);
    	glVertex3f(baseLeft,baseHeight,baseFront);
    	glVertex3f(baseRight,baseHeight,baseFront);
    	glVertex3f(baseRight,baseHeight,baseBack);
    glEnd();

    float wallHeight = baseHeight + (height/16.0);

    glColor3f(0.75,0.0,0.0);
    glBegin(GL_QUAD_STRIP);
    	glVertex3f(baseLeft,baseHeight,baseFront);
    	glVertex3f(baseLeft,wallHeight,baseFront);
    	glVertex3f(baseLeft,baseHeight,baseBack);
    	glVertex3f(baseLeft,wallHeight,baseBack);

    	glVertex3f(baseRight,baseHeight,baseBack);
    	glVertex3f(baseRight,wallHeight,baseBack);

    	glVertex3f(baseRight,baseHeight,baseFront);
    	glVertex3f(baseRight,wallHeight,baseFront);

    	glVertex3f(baseLeft,baseHeight,baseFront);
    	glVertex3f(baseLeft,wallHeight,baseFront);
    glEnd();


    //the house
    float houseFront = baseFront - (width / 14);
    float houseBack = baseBack + (width / 14);
    float houseLeft = baseLeft + (width / 14);
    float houseRight = baseRight - (width / 2);
    float houseHeight = baseHeight + (height / 4);

    glColor3f(0.0,0.0,0.75);
    glBegin(GL_QUAD_STRIP);
    	glVertex3f(houseLeft,baseHeight,houseFront);
    	glVertex3f(houseLeft,houseHeight,houseFront);
    	glVertex3f(houseLeft,baseHeight,houseBack);
    	glVertex3f(houseLeft,houseHeight,houseBack);

    	glVertex3f(houseRight,baseHeight,houseBack);
    	glVertex3f(houseRight,houseHeight,houseBack);

    	glVertex3f(houseRight,baseHeight,houseFront);
    	glVertex3f(houseRight,houseHeight,houseFront);

    	glVertex3f(houseLeft,baseHeight,houseFront);
    	glVertex3f(houseLeft,houseHeight,houseFront);
    glEnd();

    float houseRoofFront = houseFront + (width/30);
    float houseRoofBack = houseBack - (width / 30);
    float houseRoofLeft = houseLeft - (width / 26);
    float houseRoofRight = houseRight + (width / 26);
    float houseRoofHeight = houseHeight + ((houseHeight - baseHeight)/2);
    float houseRoofMiddle = (houseRoofLeft + houseRoofRight)/2;

    glColor3f(0.75f,0.75f,0.75f);
    glBegin(GL_TRIANGLE_STRIP);
    	glVertex3f(houseRoofLeft,houseHeight,houseRoofFront);
    	glVertex3f(houseRoofRight,houseHeight,houseRoofFront);
    	glVertex3f(houseRoofMiddle,houseRoofHeight,houseRoofFront);

    	glVertex3f(houseRoofRight,houseHeight,houseRoofBack);

    	glVertex3f(houseRoofMiddle,houseRoofHeight,houseRoofBack);

    	glVertex3f(houseLeft,houseHeight,houseRoofBack);

    	glVertex3f(houseRoofMiddle,houseRoofHeight,houseRoofFront);

    	glVertex3f(houseRoofLeft,houseHeight,houseRoofFront);
    glEnd();




}


void display(void)
/////////////////////////////////////////////////////////////////////////////////////////
{
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT);

	drawHouse(HEIGHT,WIDTH);
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
