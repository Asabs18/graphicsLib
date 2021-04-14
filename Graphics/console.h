#include <windows.h>
#include <WinConTypes.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <strsafe.h>
#include <time.h>
#include <stdbool.h>
#include "escape.h"

//Color Struct
typedef struct _RGB {
	size_t r;
	size_t g;
	size_t b;
}RGB_t;

typedef char char_t;

//Console Attributes struct
typedef struct _console_attributes {
	bool underline;
	bool bold;
	RGB_t foregroundColors;
	RGB_t backgroundColors;
}	consoleAttributes_t;


//A few common hard coded colors
extern RGB_t blackF;
extern RGB_t redF;
extern RGB_t greenF;
extern RGB_t yellowF;
extern RGB_t blueF;
extern RGB_t magentaF;
extern RGB_t cyanF;
extern RGB_t whiteF;

extern RGB_t blackB;
extern RGB_t redB;
extern RGB_t greenB;
extern RGB_t yellowB;
extern RGB_t blueB;
extern RGB_t magentaB;
extern RGB_t cyanB;
extern RGB_t whiteB;

//decelerations for all console related functions
inline SHORT areaOf(COORD window);
bool setFont(CONSOLE_FONT_INFOEX font, COORD fontSize, HANDLE handle);
bool sizeConsole(CONSOLE_SCREEN_BUFFER_INFO csbiInfo, COORD conSize, HANDLE handle, SMALL_RECT* conWinSize);
bool initConsole(COORD conSize, COORD fontSize);
inline COORD getConsoleSize(COORD conSize);