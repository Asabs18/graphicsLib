#pragma once
#include "draw.h"
#include <windows.h>

//#undef _DELAY_
#ifdef _DELAY_ 
#define SLEEP(ms)	Sleep(ms)
#else 
#define SLEEP(ms)
#endif // _DELAY_

bool drawChar(point_s point, char_t character, consoleAttributes_t conAttributes) {
	hideCursor();
	//Apply's all necessary escape sequences to the character
	printf(CURSOR_ABSOLUTE ANSI_CODE_RGB_FORE ANSI_CODE_RGB_BACK
		"%s%s%c%s",
		point.row, point.column,
		conAttributes.foregroundColors.r, conAttributes.foregroundColors.g, conAttributes.foregroundColors.b,
		conAttributes.backgroundColors.r, conAttributes.backgroundColors.g, conAttributes.backgroundColors.b,
		conAttributes.underline ? ANSI_CODE_UNDERLINE : "", //determines if a char should have a underline/ be bold or not
		conAttributes.bold ? ANSI_CODE_BOLD : "",
		character,
		ANSI_CODE_RESET); //after every call to draw char all console Attributes are reset
	fflush(stdout);
	return true;
}

bool drawString(point_s point, char* string, consoleAttributes_t conAttributes, COORD conSize) {
	hideCursor();
	//prints the passed in string using strlen for the length
	for (size_t i = 0; i < strlen(string); i++) {
		drawChar(point, string[i], conAttributes);
		point.column++; //prints the next char in the string the position to the right of the previous
	}
	return true;
}

bool HdrawLine(point_s startPoint, point_s endPoint, consoleAttributes_t conAttributes, char_t character) {
	hideCursor();
	//draws a horizontal line from the passed in start point to the passed in end point
	point_s currPoint = startPoint;
	//finds the difference between the start and end point and runs that amount of times
	for (size_t i = 0; i <= (endPoint.column - startPoint.column); i++) {
		drawChar(currPoint, character, conAttributes);
		//increments the column to account for a horizantal line
		currPoint.column++;
	}
	return true;
}

bool VdrawLine(point_s startPoint, point_s endPoint, consoleAttributes_t conAttributes, char_t character) {
	hideCursor();
	//draws a vertical line from the passed in start point to the passed in end point
	point_s currPoint = startPoint;
	//finds the difference between the start and end point and runs that amount of times
	for (size_t i = 0; i <= (endPoint.row - startPoint.row); i++) {
		drawChar(currPoint, character, conAttributes);
		//increments the row to account for a vertical line
		currPoint.row++;
	}
	return true;
}

bool drawDiagonalLine(point_s startPoint, point_s endPoint, char_t character, consoleAttributes_t conAttributes) {
	hideCursor();
	int differenceX = abs(endPoint.column - startPoint.column);
	int differenceY = -abs(endPoint.row - startPoint.row);
	int Xincrease = startPoint.column < endPoint.column ? 1 : -1;
	int Yincrease = startPoint.row < endPoint.row ? 1 : -1;
	int err1 = differenceX + differenceY;
	int err2;
	point_s currPoint = startPoint;
	//Bresenham's line algorithm: Creates a Diagonal line
	while (currPoint.column != endPoint.column && currPoint.row != endPoint.row) {
		drawChar(currPoint, character, conAttributes);
		err2 = 2 * err1;
		//if a certain degree of line is needed you may need to increase the column value but not the row value
		if (err2 >= differenceY) {
			err1 += differenceY;
			currPoint.column += Xincrease;
		}
		//b/c of irregularly shaped pixels, some lines need to not have the same amount of pixels of each row
		//if the line starts to differ off its path only the column will increase
		if (err2 <= differenceX) {
			err1 += differenceX;
			currPoint.row += Yincrease;
		}
	}
	return true;
}

bool drawLine(point_s startPoint, point_s endPoint, consoleAttributes_t conAttributes, char_t character, COORD conSize) {
	hideCursor();
	//checks that all points are within the window boundaries
	assert((SHORT)startPoint.row <= conSize.Y);
	assert((SHORT)endPoint.row <= conSize.Y);
	assert((SHORT)endPoint.column <= conSize.X);
	//Uses the correct line drawing function based on the users needs
	//draws a vertical line if both inputted points are on the same column
	if (startPoint.column == endPoint.column && startPoint.row < endPoint.row) {
		VdrawLine(startPoint, endPoint, conAttributes, character);
	}
	//draws a horizontal line if both inputted lines are in the same rows
	else if (startPoint.row == endPoint.row && startPoint.column < endPoint.column) {
		HdrawLine(startPoint, endPoint, conAttributes, character);
	}
	//draws a diagonal line if both inputted lines are on different rows and columns
	else if (startPoint.row != endPoint.row && startPoint.column != endPoint.column) {
		drawDiagonalLine(startPoint, endPoint, character, conAttributes);
	}
	return true;
}

bool drawRectFancy(point_s upLeftPoint, point_s downRightPoint, consoleAttributes_t conAttributes, COORD conSize, rectChar_t rectChar) {
	hideCursor();
	//checks that all points are within the window boundaries
	assert((SHORT)upLeftPoint.row < conSize.Y);
	assert((SHORT)upLeftPoint.column < conSize.X);
	assert((SHORT)downRightPoint.row < conSize.Y);
	assert((SHORT)downRightPoint.column < conSize.X);
	//determines the last two corners from the two corners passed into the function
	point_s upRightPoint;
	upRightPoint.row = upLeftPoint.row;
	upRightPoint.column = downRightPoint.column;

	point_s downLeftPoint;
	downLeftPoint.row = downRightPoint.row;
	downLeftPoint.column = upLeftPoint.column;

	//connects all 4 corners using the drawLine function which determines what kind of line to prints
	drawLine(upLeftPoint, downLeftPoint, conAttributes, rectChar.vertLine, conSize);
	drawLine(upRightPoint, downRightPoint, conAttributes, rectChar.vertLine, conSize);
	drawLine(upLeftPoint, upRightPoint, conAttributes, rectChar.horLine, conSize);
	drawLine(downLeftPoint, downRightPoint, conAttributes, rectChar.horLine, conSize);

	//draws a character at each corner because sometime you may need to put in specific corner ascii chars
	drawChar(upLeftPoint, rectChar.topLeftCor, conAttributes);
	drawChar(upRightPoint, rectChar.topRightCor, conAttributes);
	drawChar(downLeftPoint, rectChar.botLeftCor, conAttributes);
	drawChar(downRightPoint, rectChar.botRightCor, conAttributes);
	return true;
}

bool drawRect(point_s upLeftPoint, point_s downRightPoint, consoleAttributes_t conAttributes, COORD conSize, char_t character) {
	hideCursor();
	//checks that all points are within the window boundaries
	assert((SHORT)upLeftPoint.row < conSize.Y);
	assert((SHORT)upLeftPoint.column < conSize.X);
	assert((SHORT)downRightPoint.row < conSize.Y);
	assert((SHORT)downRightPoint.column < conSize.X);
	//determines the last two corners from the two corners passed into the function
	point_s upRightPoint;
	upRightPoint.row = upLeftPoint.row;
	upRightPoint.column = downRightPoint.column;

	point_s downLeftPoint;
	downLeftPoint.row = downRightPoint.row;
	downLeftPoint.column = upLeftPoint.column;

	//connects all 4 corners using the drawLine function which determines what kind of line to prints
	drawLine(upLeftPoint, downLeftPoint, conAttributes, character, conSize);
	drawLine(upRightPoint, downRightPoint, conAttributes, character, conSize);
	drawLine(upLeftPoint, upRightPoint, conAttributes, character, conSize);
	drawLine(downLeftPoint, downRightPoint, conAttributes, character, conSize);

	return true;
}

bool drawConcentricRect(bool isSpaces, consoleAttributes_t conAttributes, point_s upLeftPoint, point_s downRightPoint, char_t character, COORD conSize) {
	hideCursor();
	//depending on the isSpaces input this function calls one of two others which each draws different kinds of concentic rects
	if (isSpaces == true) {
		drawSpacesConcentricRect(conAttributes, upLeftPoint, downRightPoint, character, conSize);
	}
	else {
		drawNormalConcentricRect(conAttributes, upLeftPoint, downRightPoint, character, conSize);
	}
	return true;
}

bool drawSpacesConcentricRect(consoleAttributes_t conAttributes, point_s upLeftPoint, point_s downRightPoint, char_t character, COORD conSize) {
	hideCursor();
	//draws a smaller and smaller rectangle each iteration until the two points are equal.
	bool isSpace = true;
	do {
		//sets foreground and background equal to each others so a character prints as a solid block
		SLEEP(200);
		int rand1 = rand() % 255;
		int rand2 = rand() % 255;
		int rand3 = rand() % 255;
		if (isSpace == false) {
			conAttributes.foregroundColors.r = rand1;
			conAttributes.foregroundColors.g = rand2;
			conAttributes.foregroundColors.b = rand3;
		}
		else {
			conAttributes.foregroundColors.r = 0;
			conAttributes.foregroundColors.g = 0;
			conAttributes.foregroundColors.b = 0;
		}
		conAttributes.backgroundColors = conAttributes.foregroundColors;

		upLeftPoint.row++;
		upLeftPoint.column++;
		downRightPoint.row--;
		downRightPoint.column--;
		//uses the drawRect function to draw a smaller rectangle inside the larger parent rectangle to make it fill up
		drawRect(upLeftPoint, downRightPoint, conAttributes, conSize, character);
		if (isSpace) { isSpace = false; }
		else { isSpace = true; }
		//stops when all corners are equal to eachother
	} while (upLeftPoint.row != downRightPoint.row && upLeftPoint.column != downRightPoint.column);
	//a middle character may be left over, this will fill it
	drawChar(upLeftPoint, '\0', conAttributes);
	return true;
}

bool drawNormalConcentricRect(consoleAttributes_t conAttributes, point_s upLeftPoint, point_s downRightPoint, char_t character, COORD conSize) {
	hideCursor();
	//draws a smaller and smaller rectangle each iteration until the two points are equal.
	do {
		//sets foreground and background equal to each others so a character prints as a solid block
		int rand1 = rand() % 255;
		int rand2 = rand() % 255;
		int rand3 = rand() % 255;
		conAttributes.foregroundColors.r = rand1;
		conAttributes.foregroundColors.g = rand2;
		conAttributes.foregroundColors.b = rand3;

		conAttributes.backgroundColors = conAttributes.foregroundColors;

		upLeftPoint.row++;
		upLeftPoint.column++;
		downRightPoint.row--;
		downRightPoint.column--;
		//uses the drawRect function to draw a smaller rectangle inside the larger parent rectangle to make it fill up
		drawRect(upLeftPoint, downRightPoint, conAttributes, conSize, character);
		//stops when all corners are equal to each other
	} while (upLeftPoint.row != downRightPoint.row && upLeftPoint.column != downRightPoint.column);
	//a middle character may be left over, this will fill it
	drawChar(upLeftPoint, character, conAttributes);
	return true;
}

bool fillRect(point_s upLeftPoint, point_s downRightPoint, consoleAttributes_t conAttributes, COORD conSize, rectChar_t rectChar) {
	hideCursor();
	//sets foreground and background equal to each others so a character prints as a solid block
	conAttributes.foregroundColors.r = conAttributes.backgroundColors.r;
	conAttributes.foregroundColors.g = conAttributes.backgroundColors.g;
	conAttributes.foregroundColors.b = conAttributes.backgroundColors.b;
	//draws a smaller and smaller rectangle each iteration until the two points are equal.
	do {
		upLeftPoint.row++;
		upLeftPoint.column++;
		downRightPoint.row--;
		downRightPoint.column--;
		//uses the drawRect function to draw a smaller rectangle inside the larger parent rectangle to make it fill up
		drawRectFancy(upLeftPoint, downRightPoint, conAttributes, conSize, rectChar);
		//stops when all corners are equal to eachother
	} while (upLeftPoint.row != downRightPoint.row && upLeftPoint.column != downRightPoint.column);
	//a middle character may be left over, this will fill it
	drawChar(upLeftPoint, '\0', conAttributes);
	return true;
}

bool drawTriangle(point_s point1, point_s point2, point_s point3, consoleAttributes_t conAttributes, char_t character, COORD conSize) {
	hideCursor();
	//checks that all points are within the window boundaries
	assert((SHORT)point1.row < conSize.Y);
	assert((SHORT)point1.column < conSize.X);
	assert((SHORT)point2.row < conSize.Y);
	assert((SHORT)point2.column < conSize.X);
	assert((SHORT)point3.row < conSize.Y);
	assert((SHORT)point3.column < conSize.X);
	//connects the three passed in corners using the drawLine function which determines what kind of line is needed
	drawLine(point1, point3, conAttributes, character, conSize);
	drawLine(point2, point1, conAttributes, character, conSize);
	drawLine(point2, point3, conAttributes, character, conSize);
	return true;
}

bool drawConcentricTri(bool isSpaces, consoleAttributes_t conAttributes, point_s topPoint, point_s leftPoint, point_s rightPoint, char_t character, COORD conSize) {
	hideCursor();
	//draws two different kinds of concentric triangles depending on the parameter isSpaces
	if (isSpaces == true) {
		drawSpacesConcentricTri(conAttributes, topPoint, leftPoint, rightPoint, character, conSize);
	}
	else {
		drawNormalConcentricTri(conAttributes, topPoint, leftPoint, rightPoint, character, conSize);
	}
	return true;
}

bool drawSpacesConcentricTri(consoleAttributes_t conAttributes, point_s topPoint, point_s leftPoint, point_s rightPoint, char_t character, COORD conSize) {
	hideCursor();
	bool isSpace = true;
	//Keeps moving the bottom two points closer to the top two points and draws smaller and smaller triangles until full
	topPoint.row++;
	do {
		//sets foreground and background equal to each others so a character prints as a solid block
		int rand1 = rand() % 255;
		int rand2 = rand() % 255;
		int rand3 = rand() % 255;
		if (isSpace == false) {
			conAttributes.foregroundColors.r = rand1;
			conAttributes.foregroundColors.g = rand2;
			conAttributes.foregroundColors.b = rand3;
		}
		else {
			conAttributes.foregroundColors.r = 0;
			conAttributes.foregroundColors.g = 0;
			conAttributes.foregroundColors.b = 0;
		}
		conAttributes.backgroundColors = conAttributes.foregroundColors;

		leftPoint.row--;
		leftPoint.column++;
		rightPoint.row--;
		rightPoint.column--;
		//draws a smaller and smaller triangle inside the parent triangle to fill it up
		drawTriangle(topPoint, leftPoint, rightPoint, conAttributes, '\0', conSize);
		if (isSpace) { isSpace = false; }
		else { isSpace = true; }
		//this loop ends when all corners are equal to each other
	} while (leftPoint.row != topPoint.row && leftPoint.column != topPoint.column && rightPoint.row != topPoint.row && rightPoint.column != topPoint.column);
	return true;
}

drawNormalConcentricTri(consoleAttributes_t conAttributes, point_s topPoint, point_s leftPoint, point_s rightPoint, char_t character, COORD conSize) {
	hideCursor();
	//Keeps moving the bottom two points closer to the top two points and draws smaller and smaller triangles until full
	topPoint.row++;
	do {
		//sets foreground and background equal to each others so a character prints as a solid block
		int rand1 = rand() % 255;
		int rand2 = rand() % 255;
		int rand3 = rand() % 255;
		conAttributes.foregroundColors.r = rand1;
		conAttributes.foregroundColors.g = rand2;
		conAttributes.foregroundColors.b = rand3;
		conAttributes.backgroundColors = conAttributes.foregroundColors;

		leftPoint.row--;
		leftPoint.column++;
		rightPoint.row--;
		rightPoint.column--;
		//draws a smaller and smaller triangle inside the parent triangle to fill it up
		drawTriangle(topPoint, leftPoint, rightPoint, conAttributes, '\0', conSize);
		//this loop ends when all corners are equal to each other
	} while (leftPoint.row != topPoint.row && leftPoint.column != topPoint.column && rightPoint.row != topPoint.row && rightPoint.column != topPoint.column);
	return true;
}

bool fillTriangle(point_s topPoint, point_s leftPoint, point_s rightPoint, consoleAttributes_t conAttributes, COORD conSize) {
	hideCursor();
	//sets foreground and background equal to each others so a character prints as a solid block
	conAttributes.foregroundColors.r = conAttributes.backgroundColors.r;
	conAttributes.foregroundColors.g = conAttributes.backgroundColors.g;
	conAttributes.foregroundColors.b = conAttributes.backgroundColors.b;

	//Keeps moving the bottom two points closer to the top two points and draws smaller and smaller triangles until full
	topPoint.row++;
	do {
		leftPoint.row--;
		leftPoint.column++;
		rightPoint.row--;
		rightPoint.column--;
		//draws a smaller and smaller triangle inside the parent triangle to fill it up
		drawTriangle(topPoint, leftPoint, rightPoint, conAttributes, '\0', conSize);
		//this loop ends when all corners are equal to each other
	} while (leftPoint.row != topPoint.row && leftPoint.column != topPoint.column && rightPoint.row != topPoint.row && rightPoint.column != topPoint.column);
	return true;
}

bool drawCubeSmall(point_s point, consoleAttributes_t conAttributes, COORD conSize) {
	hideCursor();
	//creates a second point directly to the right of the first
	point_s point2;
	point2.row = point.row;
	point2.column = point.column + 1;

	//draws both points to make a more square like point
	drawChar(point, FULL_BLOCK, conAttributes);
	drawChar(point2, FULL_BLOCK, conAttributes);
	return true;
}

bool drawColorsH(COORD conSize, char_t character, point_s point, consoleAttributes_t conAttributes) {
	hideCursor();
	//generates 3 random values from 0 - 20 to serve as the amount of change each color will show
	srand((unsigned int)time(NULL));
	int random1 = rand() % 20;
	int random2 = rand() % 20;
	int random3 = rand() % 20;

	//moves to the next row and increments the color
	//runs the amount of times as their are rows in the consoles
	for (SHORT i = 0; i < conSize.Y; i++) {
		point.column = 0;
		//sets all foreground/background RGB colors
		conAttributes.foregroundColors.r += random1;
		conAttributes.foregroundColors.g += random2;
		conAttributes.foregroundColors.b += random3;
		conAttributes.backgroundColors.r += random1;
		conAttributes.backgroundColors.g += random2;
		conAttributes.backgroundColors.b += random3;
		//creates an end point the consists of the current row and the number of columns in the program
		point_s endPoint = { point.row, conSize.X };
		drawLine(point, endPoint, conAttributes, character, conSize);
		point.row++;
	}
	return true;
}

bool drawColorsV(COORD conSize, char_t character, point_s point, consoleAttributes_t conAttributes) {
	hideCursor();
	//generates 3 random values from 0 - 20 to serve as the amount of change each color will show
	srand((unsigned int)time(NULL));
	int random1 = rand() % 20;
	int random2 = rand() % 20;
	int random3 = rand() % 20;

	//moves to the next row and increments the color
	//runs the amount of times as their are columns in the consoles
	for (SHORT i = 0; i < conSize.X; i++) {
		point.row = 0;
		//sets all foreground/background RGB colors
		conAttributes.foregroundColors.r += random1;
		conAttributes.foregroundColors.g += random2;
		conAttributes.foregroundColors.b += random3;
		conAttributes.backgroundColors.r += random1;
		conAttributes.backgroundColors.g += random2;
		conAttributes.backgroundColors.b += random3;
		//creates an end point the consists of the current column and the number of rows in the program
		point_s endPoint = { conSize.Y, point.column };
		drawLine(point, endPoint, conAttributes, character, conSize);
		point.column++;
	}
	return true;
}

RGB_t Wheel(point_s WheelPos, COORD conSize) {
	hideCursor();
	//this var takes the value of WheelPos if it was layed out in one line
	int absoluteVal = WheelPos.row * conSize.X + WheelPos.column;
	//if the WheelPos is less than 85 this returns sets strip to the correct color value and returns it
	if (absoluteVal < 85) {
		RGB_t color = { absoluteVal * 3, 255 - absoluteVal * 3, 0 };
		return color;
	}
	//if the WheelPos is less than 170 this returns sets strip to the correct color value and returns it
	else if (absoluteVal < 170) {
		absoluteVal -= 85;
		RGB_t strip = { 255 - absoluteVal * 3, 0, absoluteVal * 3 };
		return strip;
	}
	//otherwise this returns sets strip to the correct color value and returns it
	else {
		absoluteVal -= 170;
		RGB_t strip = { 0, absoluteVal * 3, 255 - absoluteVal * 3 };
		return strip;
	}
}

bool rainbow(COORD conSize, consoleAttributes_t conAttributes) {
	hideCursor();
	//pos is the cursor position
	point_s pos = { 0, 0 };
	//colorPos cycles through a cycle of numbers from 0 - 255 and passes them to Wheel
	point_s colorPos = { 0, 0 };
	for (int i = 0; i < areaOf(conSize); i++) {
		//if colorPos is 255 this sets it back to 0
		if (colorPos.row * conSize.X + colorPos.column == 255) {
			colorPos.row = 0;
			colorPos.column = 0;
		}
		else if (colorPos.column == conSize.X) {
			colorPos.row++;
			colorPos.column = 0;
		}
		//increments the rows if the columns hit the boarder of the windows
		if (pos.column == conSize.X) {
			pos.row++;
			pos.column = 0;
			//pauses the loop for half a second for visual effects
			SLEEP(500);
		}
		//this gets a RGB color and sets the background to the foreground so you can only see a solid color block
		conAttributes.foregroundColors = Wheel(colorPos, conSize);
		conAttributes.backgroundColors.r = conAttributes.foregroundColors.r;
		conAttributes.backgroundColors.g = conAttributes.foregroundColors.g;
		conAttributes.backgroundColors.b = conAttributes.foregroundColors.b;
		drawChar(pos, '\0', conAttributes);
		//this increments the column each time through the loop
		pos.column++;
		colorPos.column++;
	}
	return true;
}


bool spiral(consoleAttributes_t conAttributes, COORD conSize, char_t character) {
	///NOTE: SPIRAL DOES NOT FULLEY WORK BUT INSTEAD DRAWS A CONCENTRIC RECTANGLE
	hideCursor();
	point_s currPoint = { 0,0 };
	//nextPoint is the egde of the console - 1
	point_s nextPoint = { conSize.Y - 1, conSize.X - 1 };

	//runs the amount of times to get the outer edges to the middle of the screen
	for (int i = 0; i < conSize.Y / 2; i++) {
		if (i % 2 == 0) {
			drawRect(currPoint, nextPoint, conAttributes, conSize, character);
		}
		//keeps making the Rect smaller until it meets the middle
		currPoint.row++;
		currPoint.column++;
		nextPoint.row--;
		nextPoint.column--;
	}

	return true;
}

bool drunkWalk(consoleAttributes_t conAttributes, COORD conSize, char_t character, int speed) {
	hideCursor();
	int random;
	//creates a random starting location
	point_s charLocation = { rand() % conSize.Y, rand() % conSize.X };
	while (true) {
		//draws a char then picks a random number to determine the direction to walk in next
		drawCubeSmall(charLocation, conAttributes, conSize);
		random = rand() % 4;
		//choosing what point_s value to increment(what direction to walk) depending on the random numbers
		if (random == 0 && charLocation.row < conSize.Y) {
			charLocation.row++;
		}
		else if (random == 1 && charLocation.row > 0) {
			charLocation.row--;
		}
		else if (random == 2 && charLocation.column < conSize.X) {
			charLocation.column++;
		}
		else if (random == 3 && charLocation.row > 0) {
			charLocation.column--;
		}
		//pauses the screen for half a second
		SLEEP(speed);
		//TODO: add a function that stops the walk from going back onto itself
	}
	return true;
}

bool movingLineV(consoleAttributes_t conAttributes, COORD conSize, char_t character, size_t Speed) {
	hideCursor();
	point_s startPoint = { 0, 0 };
	point_s endPoint = { conSize.Y, 0 };
	//runs once for each column in conSize
	for (int i = 0; i < conSize.X; i++) {
		//sets colors to a random RBG value and sets foreground to background to create a solid block
		int rand1 = rand() % 255;
		int rand2 = rand() % 255;
		int rand3 = rand() % 255;
		conAttributes.backgroundColors.r = rand1;
		conAttributes.backgroundColors.g = rand2;
		conAttributes.backgroundColors.b = rand3;
		conAttributes.foregroundColors = conAttributes.backgroundColors;
		//draws a colored line in each column then erases it
		drawLine(startPoint, endPoint, conAttributes, character, conSize);
		endPoint.column++;
		startPoint.column++;
		SLEEP(Speed);
		system("cls");
	}
}

bool movingLineH(consoleAttributes_t conAttributes, COORD conSize, char_t character, size_t Speed) {
	hideCursor();
	point_s startPoint = { 0, 0 };
	point_s endPoint = { 0 , conSize.X };
	//runs once for each row in conSize
	for (int i = 0; i < conSize.Y; i++) {
		//sets colors to a random RBG value and sets foreground to background to create a solid block
		int rand1 = rand() % 255;
		int rand2 = rand() % 255;
		int rand3 = rand() % 255;
		conAttributes.backgroundColors.r = rand1;
		conAttributes.backgroundColors.g = rand2;
		conAttributes.backgroundColors.b = rand3;
		conAttributes.foregroundColors = conAttributes.backgroundColors;
		//draws a colored line in each row then erases it
		drawLine(startPoint, endPoint, conAttributes, character, conSize);
		endPoint.row++;
		startPoint.row++;
		SLEEP(Speed);
		system("cls");
	}
}

bool grid(consoleAttributes_t conAttributes, COORD conSize, char_t character) {
	hideCursor();
	//sets the starting point to the top left
	point_s currPoint = { 0,0 };

	//runs once for each square in the console
	for (int i = 0; i < conSize.Y * conSize.X; i++) {
		//increments the row each time a column is filled up
		if (i == conSize.X) {
			currPoint.row++;
			currPoint.column = 0;
			i = 0;
		}
		//prints a square every other space
		if (currPoint.row % 2 == 0 && currPoint.column % 2 == 0 && currPoint.row != 0 && currPoint.column != 0) {
			drawChar(currPoint, character, conAttributes);
		}
		//increments the column
		currPoint.column++;
	}
	return true;
}


bool hideCursor() {
	//gets the current cursor info
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	//sets new cursor info to be erased
	info.dwSize = 100;
	info.bVisible = FALSE;
	//updates the cursor
	SetConsoleCursorInfo(consoleHandle, &info);
	return true;
}