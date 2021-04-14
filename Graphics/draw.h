#pragma once
#include "console.h"

//_point is a mix of row and column coordinate_t's to make a point
typedef size_t coordinate_t;
typedef struct _point {
	coordinate_t row;
	coordinate_t column;
}	point_s;

//_rect_draw contains all char_t's needed to draw a "fancyRect()"
typedef struct _rect_draw {
	char_t horLine;
	char_t vertLine;
	char_t topLeftCor;
	char_t topRightCor;
	char_t botLeftCor;
	char_t botRightCor;
}rectChar_t;

//Many decelerations for all drawing related functions
bool drawChar(point_s point, char_t character, consoleAttributes_t conAttributes);
bool drawString(point_s point, char* string, consoleAttributes_t conAttributes, COORD conSize);
bool HdrawLine(point_s startPoint, point_s endPoint, consoleAttributes_t conAttributes, char_t character);
bool VdrawLine(point_s startPoint, point_s endPoint, consoleAttributes_t conAttributes, char_t character);
bool drawDiagonalLine(point_s startPoint, point_s endPoint, char_t character, consoleAttributes_t conAttributes);
bool drawLine(point_s startPoint, point_s endPoint, consoleAttributes_t conAttributes, char_t character, COORD conSize);
bool drawRectFancy(point_s upLeftPoint, point_s downRightPoint, consoleAttributes_t conAttributes, COORD conSize, rectChar_t rectChar);
bool drawRect(point_s upLeftPoint, point_s downRightPoint, consoleAttributes_t conAttributes, COORD conSize, char_t character);
bool drawConcentricRect(bool isSpaces, consoleAttributes_t conAttributes, point_s upLeftPoint, point_s downRightPoint, char_t character, COORD conSize);
bool drawSpacesConcentricRect(consoleAttributes_t conAttributes, point_s upLeftPoint, point_s downRightPoint, char_t character, COORD conSize);
bool drawNormalConcentricRect(consoleAttributes_t conAttributes, point_s upLeftPoint, point_s downRightPoint, char_t character, COORD conSize);
bool fillRect(point_s upLeftPoint, point_s downRightPoint, consoleAttributes_t conAttributes, COORD conSize, rectChar_t rectChar);
bool drawTriangle(point_s point1, point_s point2, point_s point3, consoleAttributes_t conAttributes, char_t character, COORD conSize);
bool drawConcentricTri(bool isSpaces, consoleAttributes_t conAttributes, point_s topPoint, point_s leftPoint, point_s rightPoint, char_t character, COORD conSize);
bool drawSpacesConcentricTri(consoleAttributes_t conAttributes, point_s topPoint, point_s leftPoint, point_s rightPoint, char_t character, COORD conSize);
bool fillTriangle(point_s point1, point_s point2, point_s point3, consoleAttributes_t conAttributes, COORD conSize);
bool drawCubeSmall(point_s point, consoleAttributes_t conAttributes, COORD conSize);
bool drawColorsH(COORD conSize, char_t character, point_s point, consoleAttributes_t conAttributes);
bool drawColorsV(COORD conSize, char_t character, point_s point, consoleAttributes_t conAttributes);
RGB_t Wheel(point_s WheelPos, COORD conSize);
bool rainbow(COORD conSize, consoleAttributes_t conAttributes);
bool spiral(consoleAttributes_t conAttributes, COORD conSize, char_t character);
bool drunkWalk(consoleAttributes_t conAttributes, COORD conSize, char_t character, int speed);
bool movingLineV(consoleAttributes_t conAttributes, COORD conSize, char_t character, size_t Speed);
bool movingLineH(consoleAttributes_t conAttributes, COORD conSize, char_t character, size_t Speed);
bool grid(consoleAttributes_t conAttributes, COORD conSize, char_t character);
bool hideCursor();