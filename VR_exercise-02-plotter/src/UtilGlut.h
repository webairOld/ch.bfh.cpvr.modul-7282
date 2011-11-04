///////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
//
//  \title      GLUT Utility Class
//
//  \module     Utilities
//
//  \filename   UtilGlut.h
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
#include <string>



class UtilGlut
{
public:
	static void showFPS(const std::string& title = "");
	static void showErrorCode();
};
