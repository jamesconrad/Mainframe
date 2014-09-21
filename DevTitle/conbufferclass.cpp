#include "ConBufferClass.h"
#include <Windows.h>
#include <ctime>

#define SCREEN_HEIGHT 51
#define SCREEN_WIDTH 83

ConBufferClass::ConBufferClass()
{
}

ConBufferClass::ConBufferClass(const ConBufferClass&)
{
}

ConBufferClass::~ConBufferClass()
{
}

int ConBufferClass::Initialize()
{
	ConBufferClass::hConsole = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(L"Ascivilization");
	ConBufferClass::InitiazlizeBorder();

	ConBufferClass::beginCoords.X = 0;
	ConBufferClass::beginCoords.Y = 0;

	SetConsoleScreenBufferSize(hConsole, { SCREEN_WIDTH, SCREEN_HEIGHT });
	return 0;
}

int ConBufferClass::OutputScreen(CHAR_INFO* charData, int height, int width, COORD buffCoord)
{
	COORD buffSize;
	SMALL_RECT renderRect;
	buffSize.X = width;
	buffSize.Y = height;

	renderRect.Left = buffCoord.X + 1;
	renderRect.Top = buffCoord.Y + 1;
	renderRect.Right = buffCoord.X + buffSize.X + 1;
	renderRect.Bottom = buffCoord.Y + buffSize.Y + 1;
	
	time(&now);
	if (difftime(now, lastRender) >= 0.1)
	{
		ConBufferClass::ClearConsole(ConBufferClass::hConsole);
		ConBufferClass::RenderBorder();
		WriteConsoleOutput(ConBufferClass::hConsole, charData, buffSize, buffCoord, &renderRect);
		time(&lastRender);
	}

	//WriteConsoleOutput(ConBufferClass::hConsole, charData, buffSize, buffCoord, &renderRect);
	
	return 1;
}

//The function ClearConsole(HANDLE) was taken from www.cplusplus.com/forum/beginner/1988/3/#msg10830 to solve the security issue of using a system(char*) call.
//"Grey Wolf" (2008, July, 8) "Console Closing Down - C++ Forum" Retrieved from www.cplusplus.com/forum/beginner/1988/3/#msg10830
int ConBufferClass::ClearConsole(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return 0;

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten))
		return 0;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return 0;

	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
		return 0;

	SetConsoleCursorPosition(hConsole, coordScreen);

	return 1;
}

int ConBufferClass::InitiazlizeBorder()
{
	ConBufferClass::border = (CHAR_INFO *)malloc(sizeof(CHAR_INFO)*SCREEN_HEIGHT*SCREEN_WIDTH);
	for (int index = 0; index <= SCREEN_HEIGHT*SCREEN_WIDTH; index++)
	{//9619 for testing
		if (index == 0) ConBufferClass::border[index].Char.UnicodeChar = 9556;
		else if (index == SCREEN_WIDTH - 1) 
			ConBufferClass::border[index].Char.UnicodeChar = 9559;
		else if (index == SCREEN_HEIGHT*SCREEN_WIDTH - SCREEN_WIDTH) 
			ConBufferClass::border[index].Char.UnicodeChar = 9562;
		else if (index == SCREEN_HEIGHT*SCREEN_WIDTH - 1) 
			ConBufferClass::border[index].Char.UnicodeChar = 9565;
		else if (index == 49) 
			ConBufferClass::border[index].Char.UnicodeChar = 9574;
		else if (index == SCREEN_WIDTH * 33) 
			ConBufferClass::border[index].Char.UnicodeChar = 9568;
		else if (index == SCREEN_WIDTH * 34 - 1) 
			ConBufferClass::border[index].Char.UnicodeChar = 9571;
		else if (index == SCREEN_WIDTH * 33 + 49) 
			ConBufferClass::border[index].Char.UnicodeChar = 9577;
		//Hardcode of chatbox
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 4) - 1) 
			ConBufferClass::border[index].Char.UnicodeChar = 9571;
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 3)) 
			ConBufferClass::border[index].Char.UnicodeChar = 9568;
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 3) + 6) 
			ConBufferClass::border[index].Char.UnicodeChar = 9574;
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 1) + 6) 
			ConBufferClass::border[index].Char.UnicodeChar = 9577;
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 6) 
			ConBufferClass::border[index].Char.UnicodeChar = 9553;
		else if (index >= SCREEN_WIDTH * 48 + 1 && index <= SCREEN_WIDTH * 49 - 2) 
			ConBufferClass::border[index].Char.UnicodeChar = 9552;
		//Chat:
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 1)
		{
			ConBufferClass::border[index].Char.UnicodeChar = 67;
			ConBufferClass::border[index].Attributes = 0x0007;
		}
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 2)
		{
			ConBufferClass::border[index].Char.UnicodeChar = 104;
			ConBufferClass::border[index].Attributes = 0x0007;
		}
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 3)
		{
			ConBufferClass::border[index].Char.UnicodeChar = 97;
			ConBufferClass::border[index].Attributes = 0x0007;
		}
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 4)
		{
			ConBufferClass::border[index].Char.UnicodeChar = 116;
			ConBufferClass::border[index].Attributes = 0x0007;
		}
		else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 5)
		{
			ConBufferClass::border[index].Char.UnicodeChar = 58;
			ConBufferClass::border[index].Attributes = 0x0007;
		}
		//is it in row 1 or 33 or SCREEN_HEIGHT?
		else if (index < SCREEN_WIDTH || (index > SCREEN_WIDTH * 33 && index < SCREEN_WIDTH * 34 - 1) || (index > (SCREEN_HEIGHT - 1) * SCREEN_WIDTH && index < SCREEN_HEIGHT * SCREEN_WIDTH - 1)) 
			ConBufferClass::border[index].Char.UnicodeChar = 9552;
		//is it in col 49 and above the middle bar?
		else if (index >= SCREEN_WIDTH && index % SCREEN_WIDTH == 49 && index < SCREEN_WIDTH * 34) 
			ConBufferClass::border[index].Char.UnicodeChar = 9553;
		//is it in col 1 or SCREEN_WIDTH
		else if (index >= SCREEN_WIDTH && index <= SCREEN_WIDTH*SCREEN_HEIGHT && (index % SCREEN_WIDTH == 0 || index % SCREEN_WIDTH == SCREEN_WIDTH - 1)) 
			ConBufferClass::border[index].Char.UnicodeChar = 9553;
		else 
			ConBufferClass::border[index].Char.UnicodeChar = 32;
		if (ConBufferClass::border[index].Attributes != 0x0007)
			ConBufferClass::border[index].Attributes = 0x0004 | 0x0008;
	}
	return 1;
}

int ConBufferClass::RenderBorder()
{
	SMALL_RECT borderRect;
	borderRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	WriteConsoleOutput(ConBufferClass::hConsole, ConBufferClass::border, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0, 0 }, &borderRect);
	
	return 1;
}