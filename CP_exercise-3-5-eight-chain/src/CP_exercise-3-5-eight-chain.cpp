//============================================================================
// Name        : CP_exercise-3-5-eight-chain.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Image.h"
#include <sstream>
#include <fstream>
#include <queue>


using namespace cpvrIPL;

using namespace std;

struct PixelCoord {
	int x;
	int y;
};



void label(PixelCoord startPoint,PixelCoord currentPoint,int searchCode,BImage &image,queue<int> &chain);

string str(int number)
{
	std::string s;
	std::stringstream out;
	out << number;
	return out.str();
}

// auxiliary function to remove a detected object
// to background using flood fill
void floodImages( BImage& bImage,GImage& gImage, int x, int y )
{
	bool inFrame = x<bImage.Width() && x >=0 && y<bImage.Height() && y>=0;
	if( ! inFrame ) return;
	if( ! bImage(x,y) ) return;
	bImage(x,y) = false;
	gImage(x,y) = 100;
	floodImages( bImage,gImage, x+1, y );
	floodImages( bImage,gImage, x-1, y );
	floodImages( bImage,gImage, x, y+1 );
	floodImages( bImage,gImage, x, y-1 );
	floodImages( bImage,gImage, x+1, y+1 );
	floodImages( bImage,gImage, x-1, y+1 );
	floodImages( bImage,gImage, x+1, y-1 );
	floodImages( bImage,gImage, x-1, y-1 );
}

int main() {
		GImage greyScaleImage;
		BImage binaryImage;
		try {
		greyScaleImage = GImage("res/images/artificial1.bmp");
		binaryImage = BImage("res/images/artificial1.bmp");
		} catch (cpvrIPLException & e) {
			return 1;
		}
		showImage(greyScaleImage);

		const int xDirection[] = { 1 , 1 , 0 , -1 , -1 , -1 , 0 , 1 };
		const int yDirection[] = { 0 , -1 , -1 , -1 , 0 , 1 , 1 , 1 };

		int objNr = 0;
		//cout << binaryImage.Height() << endl;
		for (int y=0; y < binaryImage.Height(); y++) {

			for (int x=0; x < binaryImage.Width(); x++) {

				binaryImage.isInRange(0,0);
				if (binaryImage(x,y) == 1) {
					std::string codeText;
					PixelCoord curPoint;
					curPoint.x = x;
					curPoint.y = y;
					int lastCode = 0;

					bool firstLoop = true;
					while (x != curPoint.x || y != curPoint.y || firstLoop) {
						firstLoop = false;
						int searchCode = (lastCode + 2)%8;

	                    for( int cod=0; cod<8; cod++ ) {
							int code = (searchCode-cod + 8) % 8; //do so, because minus values aren't correct
							PixelCoord nextPoint;
							nextPoint.x = curPoint.x +  xDirection[code];
							nextPoint.y = curPoint.y +  yDirection[code];
							//pixel must be in image
							if (binaryImage.isInRange(nextPoint.x,nextPoint.y)) {
								//check if it is set
								if (binaryImage(nextPoint.x,nextPoint.y)) {
									codeText += (char)( code + '0' );
									curPoint.x = nextPoint.x;
									curPoint.y = nextPoint.y;
									lastCode = code;
									break;
								}

							}
	                    }
					}
					objNr++;
					string fileName = "res/chains/chainCode" + str(objNr) + ".txt";

					ofstream chainFile( fileName.c_str() );
					chainFile << codeText << std::endl;
					chainFile.close();
					floodImages( binaryImage,greyScaleImage, x, y );
					showImage(greyScaleImage);
				}
			}
		}
		cout << "found " << objNr << " objects" << endl;
	return 0;
}
