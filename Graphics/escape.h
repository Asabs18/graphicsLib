#pragma once

//defines the underline reset and bold escape codes
#define ESC "\x1B"
#define ANSI_CODE_RESET         ESC"[00m"
#define ANSI_CODE_BOLD          ESC"[1m"
#define ANSI_CODE_UNDERLINE		ESC"[4m"

#define RESET(string)			ANSI_CODE_RESET string
#define BOLD(string)			ANSI_CODE_BOLD string
#define UNDERLINE(string)		ANSI_CODE_UNDERLINE string

//defines the escape code for RGB values
#define ANSI_CODE_RGB_FORE			ESC"[38;2;%d;%d;%dm"
#define ANSI_CODE_RGB_BACK			ESC"[48;2;%d;%d;%dm"

#define RGB_F(string)			ANSI_CODE_RGB_FORE string
#define RGB_B(string)			ANSI_CODE_RGB_BACK string

//defines the escape codes for cursor movement
#define CURSOR_ABSOLUTE			ESC"\033[%d;%dH"

#define C_ABSOLUTE(string)		CURSOR_ABSOLUTE string

//defines extended ascii characters
#define LIGHT_SHADE							0xB0
#define MEDIUM_SHADE						0xB1
#define DARK_SHADE							0xB2
#define DOUBLE_LINE_DOWNLEFT_CORNER			0xC8
#define DOUBLE_LINE_HOR						0xCD
#define DOUBLE_LINE_VERT					0xBA
#define DOUBLE_LINE_UPRIGHT_CORNER			0xBB
#define DOUBLE_LINE_UPLEFT_CORNER			0xC9
#define DOUBLE_LINE_DOWNRIGHT_CORNER		0xBC
#define DOUBLE_LINE_DOWN_HOR				0xCB
#define DOUBLE_LINE_FOUR_PRONG				0xCE
#define DOUBLE_LINE_RIGHT_VERT				0xCC
#define DOUBLE_LINE_LEFT_VERT				0xB9
#define DOUBLE_LINE_UP_HOR					0xCA
#define LINE_VERT							0xB3
#define LINE_VERT_LEFT_PRONG				0xB4
#define LINE_UP_RIGHT_CORNER				0xBF
#define LINE_DOWN_LEFT_CORNER				0xC0
#define LINE_DOWN_RIGHT_CORNER				0xD9
#define LINE_UP_LEFT_CORNER					0xDA
#define LINE_HOR_UP_PRONG					0xC1
#define LINE_HOR_DOWN_PRONG					0xC2
#define LINE_VERT_RIGHT_PRONG				0xC3
#define LINE_HOR							0xC4
#define LINE_FOUR_PRONG						0xC5
#define FULL_BLOCK							0xDB
#define LOWER_HALF_BLOCK					0xDC
#define LEFT_HALF_BLOCK						0xDD
#define RIGHT_HALF_BLOCK					0xDE
#define UPPER_HALF_BLOCK					0xDF
#define SMALL_BLOCK							0xFE