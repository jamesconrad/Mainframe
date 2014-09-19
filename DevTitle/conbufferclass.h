#ifndef CONBUFFERCLASS_H
#define CONBUFFERCLASS_H

#include <Windows.h>



class ConBufferClass {
private:
	HANDLE hBuffer,hConsole;
	COORD beginCoords;
	SMALL_RECT rect;
	DWORD nWritten;
	bool hBuffActive = false;
public:
	ConBufferClass();
	ConBufferClass(const ConBufferClass&);
	~ConBufferClass();
	
	int Initialize();
	int SwapBuffer();
	int OutputScreen(CHAR_INFO *, int, COORD);
	int ClearConsole(HANDLE);
};

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
#endif