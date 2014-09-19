#include "ConBufferClass.h"
#include <Windows.h>

/*
ConBufferClass();
ConBufferClass(const ConBufferClass&);
~ConBufferClass();

int initialize();
int activateBuffer();
*/

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
	ConBufferClass::hBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	ConBufferClass::beginCoords.X = 0;
	ConBufferClass::beginCoords.Y = 0;
	SetConsoleCursorPosition(hBuffer, beginCoords);
	return 0;
}

int ConBufferClass::SwapBuffer()
{
	if (ConBufferClass::hBuffActive)
	{
		SetConsoleActiveScreenBuffer(ConBufferClass::hConsole);
	}
	else
	{
		SetConsoleActiveScreenBuffer(ConBufferClass::hBuffer);
		ConBufferClass::hBuffActive = true;
	}

	return 0;
}
//COORD buffSize;
//buffSize.X = sizeof(char*); buffSize.Y = 1
//SMALL_RECT renderRect;
//renderRect.Left = x; renderRect.Top = y; renderRect.Right = x + buffSize.X; renderRect.Bottom = y + buffSize.Y;
//COORD buffCoord;
//buffCoord.X = x; buffCoord.Y = y;
int ConBufferClass::OutputScreen(CHAR_INFO charData[], int length, COORD buffCoord)
{
	COORD buffSize;
	SMALL_RECT renderRect;

	buffSize.X = length;
	buffSize.Y = 1;

	renderRect.Left = buffCoord.X;
	renderRect.Top = buffCoord.Y;
	renderRect.Right = buffCoord.X + buffSize.X;
	renderRect.Bottom = buffCoord.Y + buffSize.Y;

	WriteConsoleOutput(ConBufferClass::hBuffer, charData, buffSize, buffCoord, &renderRect);
	
	return 1;
}

//The function cls(HANDLE) was taken from www.cplusplus.com/forum/beginner/1988/3/#msg10830 to solve the security issue of using a system(char*) call.
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

/*

HANDLE hConsole, hBuffer;
hConsole = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
bool result;
//Initialzing the Buffer, should be moved to a class
hBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
COORD beginCoords;
beginCoords.X = 0;
beginCoords.Y = 0;
SetConsoleCursorPosition(hBuffer, beginCoords);
DWORD nWritten;
SetConsoleActiveScreenBuffer(hBuffer);

SMALL_RECT rect;

rect.Left = 0;
rect.Top = 0;
rect.Right = 15;
rect.Bottom = 1;

COORD arrCoord;
arrCoord.X = 15;
arrCoord.Y = 1;

CHAR_INFO outputData[15];
for (int i = 0; i < 15; i++)
outputData[i].Attributes = 0x0001 | 0x0002 | 0x0004;
outputData[0].Char.UnicodeChar = 73;//73
outputData[1].Char.UnicodeChar = 39;//39
outputData[2].Char.UnicodeChar = 109;
outputData[3].Char.UnicodeChar = 32;
outputData[4].Char.UnicodeChar = 116;
outputData[5].Char.UnicodeChar = 104;
outputData[6].Char.UnicodeChar = 101;
outputData[7].Char.UnicodeChar = 32;
outputData[8].Char.UnicodeChar = 98;
outputData[9].Char.UnicodeChar = 117;
outputData[10].Char.UnicodeChar = 102;
outputData[11].Char.UnicodeChar = 102;
outputData[12].Char.UnicodeChar = 101;
outputData[13].Char.UnicodeChar = 114;
outputData[14].Char.UnicodeChar = 33;
result = WriteConsoleOutput(hBuffer, outputData, arrCoord, beginCoords,  &rect);

*/