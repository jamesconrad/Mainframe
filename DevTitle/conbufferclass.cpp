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
	hConsole = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(L"Mainframe");
	
	playerColour[0] = 0x0001 | 0x0008;
	playerColour[1] = 0x0002 | 0x0008;
	playerColour[2] = 0x0003 | 0x0008;
	playerColour[3] = 0x0004 | 0x0008;
	playerColour[4] = 0x0005 | 0x0008;
	playerColour[5] = 0x0006 | 0x0008;
	playerColour[6] = 0x0007 | 0x0008;
	

	border = (CHAR_INFO *)malloc(sizeof(CHAR_INFO)*SCREEN_HEIGHT*SCREEN_WIDTH);
	InitiazlizeBorder();

	beginCoords.X = 0;
	beginCoords.Y = 0;

	unitsRendered = false;

	SetConsoleScreenBufferSize(hConsole, { SCREEN_WIDTH, SCREEN_HEIGHT });
	return 0;
}

int ConBufferClass::OutputScreen(CHAR_INFO* charData, CHAR_INFO* unitData, int height, int width, COORD buffCoord, COORD frameCoords)
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
	if (difftime(now, lastRender) >= 0.0)
	{
		ClearConsole(hConsole, frameCoords);
		RenderBorder();
		if (!unitsRendered)
		{
			WriteConsoleOutput(hConsole, unitData, buffSize, buffCoord, &renderRect);
			unitsRendered = true;
		}
		else
		{
			WriteConsoleOutput(hConsole, charData, buffSize, buffCoord, &renderRect);
			unitsRendered = false;
		}
		time(&lastRender);
	}
	
	return 1;
}

//The function ClearConsole(HANDLE) was taken from www.cplusplus.com/forum/beginner/1988/3/#msg10830 to solve the security issue of using a system(char*) call.
//"Grey Wolf" (2008, July, 8) "Console Closing Down - C++ Forum" Retrieved from www.cplusplus.com/forum/beginner/1988/3/#msg10830
int ConBufferClass::ClearConsole(HANDLE hConsole, COORD frameCoords)
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

	SetConsoleCursorPosition(hConsole, frameCoords);

	return 1;
}

int ConBufferClass::UpdateBorderColour(int playerNum)
{
	for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; ++i)
		border[i].Attributes = playerColour[playerNum];
	return 1;
}

int ConBufferClass::InitiazlizeBorder()
{
	for (int index = 0; index <= SCREEN_HEIGHT*SCREEN_WIDTH; index++)
	{//9619 for testing
		if (index == 0) ConBufferClass::border[index].Char.UnicodeChar = 9556;
		else if (index == SCREEN_WIDTH - 1) 
			border[index].Char.UnicodeChar = 9559;
		else if (index == SCREEN_HEIGHT*SCREEN_WIDTH - SCREEN_WIDTH) 
			border[index].Char.UnicodeChar = 9562;
		else if (index == SCREEN_HEIGHT*SCREEN_WIDTH - 1) 
			border[index].Char.UnicodeChar = 9565;
		else if (index == 49) 
			border[index].Char.UnicodeChar = 9574;
		//Hardcode of turn/gold box
		else if (index == SCREEN_WIDTH * 2 + 49)
			border[index].Char.UnicodeChar = 9568;
		else if (index == SCREEN_WIDTH * 3 - 1)
			border[index].Char.UnicodeChar = 9571;
		else if (index >= SCREEN_WIDTH * 2 + 49 && index <= SCREEN_WIDTH * 3 - 2)
			border[index].Char.UnicodeChar = 9552;

		else if (index == SCREEN_WIDTH * 33) 
			border[index].Char.UnicodeChar = 9568;
		else if (index == SCREEN_WIDTH * 34 - 1) 
			border[index].Char.UnicodeChar = 9571;
		else if (index == SCREEN_WIDTH * 33 + 49) 
			border[index].Char.UnicodeChar = 9577;
		////Hardcode of chatbox
		//else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 2) - 1) 
		//	border[index].Char.UnicodeChar = 9571;
		//else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 3)) 
		//	border[index].Char.UnicodeChar = 9568;
		//else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 3) + 6) 
		//	border[index].Char.UnicodeChar = 9574;
		//else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 1) + 6) 
		//	border[index].Char.UnicodeChar = 9577;
		//else if (index == SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 6) 
		//	border[index].Char.UnicodeChar = 9553;
		//else if (index >= SCREEN_WIDTH * 48 + 1 && index <= SCREEN_WIDTH * 49 - 2) 
		//	border[index].Char.UnicodeChar = 9552;
		//is it in row 1 or 33 or SCREEN_HEIGHT?
		else if (index < SCREEN_WIDTH || (index > SCREEN_WIDTH * 33 && index < SCREEN_WIDTH * 34 - 1) || (index > (SCREEN_HEIGHT - 1) * SCREEN_WIDTH && index < SCREEN_HEIGHT * SCREEN_WIDTH - 1)) 
			border[index].Char.UnicodeChar = 9552;
		//is it in col 49 and above the middle bar?
		else if (index >= SCREEN_WIDTH && index % SCREEN_WIDTH == 49 && index < SCREEN_WIDTH * 34) 
			border[index].Char.UnicodeChar = 9553;
		//is it in col 1 or SCREEN_WIDTH
		else if (index >= SCREEN_WIDTH && index <= SCREEN_WIDTH*SCREEN_HEIGHT && (index % SCREEN_WIDTH == 0 || index % SCREEN_WIDTH == SCREEN_WIDTH - 1)) 
			border[index].Char.UnicodeChar = 9553;
		else 
			border[index].Char.UnicodeChar = 32;
		
		border[index].Attributes = 0x0004 | 0x0008;
	}
	//Time to fill in text
	//Chat: text input starts at 4073
	/*int string[4] = { 67, 104, 97, 116 };
	for (int i = 0; i < 4; i++)
	{
		border[SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 1 + i].Char.UnicodeChar = string[i];
		border[SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 1 + i].Attributes = 0x0007;
	}
	border[SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 1 + 4].Char.UnicodeChar = 58;
	border[SCREEN_WIDTH * (SCREEN_HEIGHT - 2) + 1 + 4].Attributes = 0x0007;*/
	//Turn: turn num starts at 139
	int string[4] = { 84, 117, 114, 110 };
	
	for (int i = 0; i < 4; i++)
	{
		border[SCREEN_WIDTH + 50 + i].Char.UnicodeChar = string[i];
		border[SCREEN_WIDTH + 50 + i].Attributes = 0x0007;
	}
	border[SCREEN_WIDTH + 50 + 4].Char.UnicodeChar = 58;
	border[SCREEN_WIDTH + 50 + 4].Attributes = 0x0007;
	//Gold: num starts at 154
	int stringq[7];
	stringq[0] = 84;
	stringq[1] = 104;
	stringq[2] = 114;
	stringq[3] = 101;
	stringq[4] = 97;
	stringq[5] = 100;
	stringq[6] = 115;
	for (int i = 0; i < 7; i++)
	{
		border[SCREEN_WIDTH + 65 + i].Char.UnicodeChar = stringq[i];
		border[SCREEN_WIDTH + 65 + i].Attributes = 0x0007;
	}
	border[SCREEN_WIDTH + 65 + 7].Char.UnicodeChar = 58;
	border[SCREEN_WIDTH + 65 + 7].Attributes = 0x0007;

	return 1;
	
}

int ConBufferClass::RenderBorder()
{
	SMALL_RECT borderRect;
	borderRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	WriteConsoleOutput(hConsole, border, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0, 0 }, &borderRect);
	
	return 1;
}