#include "draw.h"
#include <stdint.h>
#include <conio.h>

int main(int argc, char* argv[]) {
	COORD fontSize;
	fontSize.X = atoi(argv[1]);
	fontSize.Y = atoi(argv[2]);
	COORD conSize;
	conSize.X = atoi(argv[3]);
	conSize.Y = atoi(argv[4]);
	bool works = initConsole(conSize, fontSize);
	assert(works != false);

	point_s point;
	point.row = atoi(argv[5]);
	point.column = atoi(argv[6]);
	char_t character = '\0';
	consoleAttributes_t conAttributes;
	conAttributes.bold = false;
	conAttributes.underline = false;

	RGB_t colorsF;
	RGB_t colorsB;
	colorsF.r = atoi(argv[7]);
	colorsF.g = atoi(argv[8]);
	colorsF.b = atoi(argv[9]);
	colorsB.r = atoi(argv[10]);
	colorsB.g = atoi(argv[11]);
	colorsB.b = atoi(argv[12]);

	conAttributes.foregroundColors = colorsF;
	conAttributes.backgroundColors = colorsB;


	///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
	///under the green tags are function calls, uncomment them to  ///
	///use the mentioned function. functions with ^'s next to them ///
	///need you to uncomment some point/conAttributes def's above  ///
	///them - Aidan Sabatini *I changed the command line arguments ///
	/// numbers when I zipped the file.							   ///
	///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///


	///DRAWS A GRID
	//grid(conAttributes, conSize, character);

	///MOVING LINE VERTICAL
	//movingLineV(conAttributes, conSize, character, 10);
	//movingLineH(conAttributes, conSize, character, 10);

	///DRUNK WALK
	drunkWalk(conAttributes, conSize, character, 50);

	///DRAWS A SPIRAL
	//spiral(conAttributes, conSize, character);

	///DRAWS A RAINBOW
	//rainbow(conSize, conAttributes);


	///DRAWS A SMALL CUBE
	//point_s point1;
	//point1.row = 10;
	//point1.column = 10;
	//drawCubeSmall(point1, conAttributes, conSize);

	///DRAWS A TRIANGLE
	//point_s point1;
	//point1.row = 10;
	//point1.column = 10;

	//point_s point2;
	//point2.row = 20;
	//point2.column = 0;
	//
	//point_s point3;
	//point3.row = 20;
	//point3.column = 20;

	//drawTriangle(point1, point2, point3, conAttributes, '0', conSize);
	///DRAWS CONCENTRIC TRIANGLE ^^
	//drawConcentricTri(true, conAttributes, point1, point2, point3, character, conSize);

	///FILLS A TRIANGLE^^
	//fillTriangle(point1, point2, point3, conAttributes, conSize);

	///DRAWS A RECTANGLE
	//point_s upLeft;
	//upLeft.row = 2;
	//upLeft.column = 10;

	//point_s downRight;
	//downRight.row = 40;
	//downRight.column = 49;

	//rectChar_t rectChar;
	//rectChar.horLine = LINE_HOR;
	//rectChar.vertLine = LINE_VERT;
	//rectChar.topLeftCor = LINE_UP_LEFT_CORNER;
	//rectChar.topRightCor = LINE_UP_RIGHT_CORNER;
	//rectChar.botLeftCor = LINE_DOWN_LEFT_CORNER;
	//rectChar.botRightCor = LINE_DOWN_RIGHT_CORNER;

	//drawRect(upLeft, downRight, conAttributes, conSize, '0');
	//drawRectFancy(upLeft, downRight, conAttributes, conSize, rectChar);

	///DRAWS CONCENTRIC RECTANGLE ^^
	//drawConcentricRect(true, conAttributes, upLeft, downRight, character, conSize);

	///FILLS A RECT^^
	//conAttributes.backgroundColors.r = 255;
	//conAttributes.backgroundColors.g = 0;
	//conAttributes.backgroundColors.b = 0;
	//fillRect(upLeft, downRight, conAttributes, conSize, rectChar);



	///DRAWS A LINE
	//point_s lineStart;
	//lineStart.row = 10;
	//lineStart.column = 10;

	//point_s lineEnd;
	//lineEnd.row = 20; //15, 20 
	//lineEnd.column = 20; //10, 20

	//drawLine(lineStart, lineEnd, conAttributes, '\\', conSize);


	///DRAWS A STRING
	//point.column++;
	//drawString(point, "My Name is Aidan", conAttributes, conSize);


	///DRAWS A CHAR
	//drawChar(point, character, conAttributes);


	///FILLS SCREEN WITH COLORS
	//drawColorsH(conSize, character, point, conAttributes);
	//while (_kbhit() == 0) {}
	//drawColorsV(conSize, character, point, conAttributes);
	while (_kbhit() == 0) {}
} 