///////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
//
//  \title      GLUT Utility Class
//
//  \module     Utilities
//
//  \filename   UtilGlut.cpp
//
//  \brief      General utility class for OpenGL/GLUT support.
//
//  \subversion
//     Last Subversion commit $Author:$
//     Last Subversion commit   $Date:$
//     Last Subversion File $Revision:$
//
//  \history
//     yyyy-mm-dd   Version   Author   Comment
//     2006-11-06   0.1.00    klu      initial file release
//     2009-10-02   0.1.01    schar9   Mac OS X compatible, C++ standard conform
//  \endverbatim
*/
///////////////////////////////////////////////////////////////////////////////////////////////////




// system includes ////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>

#include "UtilGlut.h"
using namespace std;





void UtilGlut::showErrorCode()
///////////////////////////////////////////////////////////////////////////////////////////////////
{
	GLenum errCode;
	const GLubyte *errString;

	if ((errCode = glGetError()) != GL_NO_ERROR)
	{
		errString = gluErrorString(errCode);
		std::cout << "OpenGL Error Code: " << errCode << " (" << errString << ")" << std::endl;
	}
}
// end: UtilGlut::showErrorCode() /////////////////////////////////////////////////////////////////




void UtilGlut::showFPS(const string& title)
///////////////////////////////////////////////////////////////////////////////////////////////////
{
	// replace current GLUT window title with FPS string ("append" can not be implemented,
	// because there is no GLUT function to get the current window title.)

	// calculate frames per second (FPS)
	static int frame = 0;
	static int time = 0;
	static int timebase = 0;
	static char str[128];

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000)
	{
		sprintf(str,"%s ( FPS: %4.2f )", title.c_str(), frame*1000.0/(time-timebase));
		glutSetWindowTitle(str);
		timebase = time;
		frame = 0;
	}
}
// end: UtilGlut::showFPS() /////////////////////////////////////////////////////////////////////
