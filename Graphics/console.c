#include "console.h"
///PREDEFINED  COLORS
RGB_t black = { 0, 0, 0 };
RGB_t red = { 255, 0, 0 };
RGB_t green = { 0, 255, 0 };
RGB_t yellow = { 255, 255, 0 };
RGB_t blue = { 0, 0, 255 };
RGB_t magenta = { 255, 0, 255 };
RGB_t cyan = { 0, 255, 255 };
RGB_t white = { 255, 255, 255 };

//finds the area of a COORD data type
inline SHORT areaOf(COORD window) {
	return window.X * window.Y;
}

//Sets the Font size
bool setFont(CONSOLE_FONT_INFOEX font, COORD fontSize, HANDLE handle) {
	bool fontSet = true;
	//Gets the current font and returns true if successful 
	if (!GetCurrentConsoleFontEx(handle, true, &font)) {
		fontSet = false;
	}
	//sets fonts size attribute to the passed in font size
	font.dwFontSize.X = fontSize.X;
	font.dwFontSize.Y = fontSize.Y;
	//calls SetCurretConsoleFontEx to update the current font and returns true if successful
	if (!SetCurrentConsoleFontEx(handle, true, &font)) {
		fontSet = false;
	}
	return fontSet;
}

bool sizeConsole(CONSOLE_SCREEN_BUFFER_INFO csbiInfo, COORD conSize, HANDLE handle, SMALL_RECT* conWinSize) {
	int output;
	//if the areas of the current console window is bigger than conSize call resize functions in the following order
	if (areaOf(csbiInfo.dwSize) > areaOf(conSize)) {
		//changes the console windows size
		output = SetConsoleWindowInfo(handle, true, conWinSize);
		//insures the function does not return an error code (asserts)
		assert(output != 0);
		//changes the consoles buffer size
		output = SetConsoleScreenBufferSize(handle, conSize);
		assert(output != 0);
	}
	//if the areas of the current console window is smaller than conSize call resize functions in the following order
	else if (areaOf(csbiInfo.dwSize) < areaOf(conSize)) {
		//changes the screen buffers size
		output = SetConsoleScreenBufferSize(handle, conSize);
		//insures the function does not return an error code (asserts)
		assert(output != 0);
		//changes the windows size
		output = SetConsoleWindowInfo(handle, true, conWinSize);
		assert(output != 0);
	}
	return true;
}

bool initConsole(COORD conSize, COORD fontSize) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	if (!GetConsoleMode(handle, &dwMode)) {
		return false;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(handle, dwMode)) {
		return false;
	}
	SMALL_RECT conWinSize;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	COORD winCoords;
	CONSOLE_FONT_INFOEX font = { .cbSize = sizeof(CONSOLE_FONT_INFOEX) };
	//Sets the Font size
	bool fontSet = setFont(font, fontSize, handle);
	assert(fontSet == true);
	//Gets the coordinates for the largest possible window and makes sure conSize is in range
	winCoords = GetLargestConsoleWindowSize(handle);
	if (winCoords.X == 0 && winCoords.Y == 0) {
		//Unable to retrieve largest possible window coordinates
		assert(false);
	}
	if (conSize.Y > winCoords.Y - 1 || conSize.X > winCoords.X - 1) {
		return false;
	}
	//sets conWinSize from the values from conSize
	conWinSize.Left = 0;
	conWinSize.Top = 0;
	conWinSize.Right = conSize.X - 1;
	conWinSize.Bottom = conSize.Y - 1;
	//gets the current size of the console screen buffer so we can know if conSize will make it bigger or smaller
	if (!GetConsoleScreenBufferInfo(handle, &csbiInfo)) {
		//Unable to retrieve console screen buffer data
		assert(false);
	}
	//resizes the console window using SetConsole functions calling certain functions first depending on current size of console window
	bool works = sizeConsole(csbiInfo, conSize, handle, &conWinSize);
	assert(works != false);
	//TODO: make an API call to [SetConsoleMode function - Windows Console | Microsoft Docs](https://bit.ly/3gnS1ZW)
	HMENU sysMenu = GetSystemMenu(GetConsoleWindow(), false);
	DeleteMenu(sysMenu, SC_SIZE, MF_BYCOMMAND);
	DeleteMenu(sysMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	return works;
}

inline COORD getConsoleSize(COORD conSize) {
	return conSize;
}