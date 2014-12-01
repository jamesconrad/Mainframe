#include "conbufferclass.h"
#include <Windows.h>
#include "entityclass.h"
#include <iostream>

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


int ConvertString(const char * text, CHAR_INFO * result)
{
	wchar_t * converted = (wchar_t*)malloc(sizeof(wchar_t)* strlen(text));
	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text, strlen(text)*sizeof(char), converted, strlen(text));
	for (int i = 0; i < strlen(text); i++)
	{
		result[i].Char.UnicodeChar = text[i];
		result[i].Attributes = 0x007;
	}
	free(converted);
	return 1;
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

	InitializeBorder();
	InitializeUnitInfo();

	beginCoords.X = 0;
	beginCoords.Y = 0;

	SMALL_RECT screenSize;
	screenSize.Left = 0;
	screenSize.Right = SCREEN_WIDTH - 1;
	screenSize.Top = 0;
	screenSize.Bottom = SCREEN_HEIGHT - 1;

	SetConsoleScreenBufferSize(hConsole, { SCREEN_WIDTH, SCREEN_HEIGHT });
	SetConsoleWindowInfo(hConsole, true, &screenSize);
	int err = GetLastError();

	numChar = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* 4);
	converted = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* 4);
	unitName = new CHAR_INFO[16];
	wconverted = new wchar_t[16];

	class_ModelLoader.Initialize();

	return 0;
}

int ConBufferClass::OutputScreen(CHAR_INFO* unitData, int height, int width, COORD buffCoord, int frame, EntityClass selectedUnit)
{
	COORD buffSize;
	SMALL_RECT renderRect;
	buffSize.X = width;
	buffSize.Y = height;

	renderRect.Left = buffCoord.X + 1;
	renderRect.Top = buffCoord.Y + 1;
	renderRect.Right = buffCoord.X + buffSize.X + 1;
	renderRect.Bottom = buffCoord.Y + buffSize.Y + 1;

	CHAR_INFO* tmp = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* 4);
	tmp[0] = unitData[frame + width + 1];
	tmp[1] = unitData[frame + width - 1];
	tmp[2] = unitData[frame - width + 1];
	tmp[3] = unitData[frame - width - 1];

	if ((frame + 1) % width != 0)
	{
		unitData[frame + width + 1].Char.UnicodeChar = '\\';
		unitData[frame - width + 1].Char.UnicodeChar = '/';
		unitData[frame + width + 1].Attributes = 0x0007 | 0x0008;
		unitData[frame - width + 1].Attributes = 0x0007 | 0x0008;
	}

	if ((frame + 1) % width - 1 != 0)
	{
		unitData[frame - width - 1].Char.UnicodeChar = '\\';
		unitData[frame + width - 1].Char.UnicodeChar = '/';
		unitData[frame + width - 1].Attributes = 0x0007 | 0x0008;
		unitData[frame - width - 1].Attributes = 0x0007 | 0x0008;
	}

	RenderUnitInfo(selectedUnit);
	WriteConsoleOutput(hConsole, unitData, buffSize, buffCoord, &renderRect);

	unitData[frame + width + 1] = tmp[0];
	unitData[frame + width - 1] = tmp[1];
	unitData[frame - width + 1] = tmp[2];
	unitData[frame - width - 1] = tmp[3];

	free(tmp);

	return 1;
}
int ConBufferClass::OutputScreen(CHAR_INFO* worldMap, CHAR_INFO* unitData, int height, int width, COORD buffCoord, int frame)
{
	COORD buffSize;
	SMALL_RECT renderRect;
	buffSize.X = width;
	buffSize.Y = height;

	renderRect.Left = buffCoord.X + 1;
	renderRect.Top = buffCoord.Y + 1;
	renderRect.Right = buffCoord.X + buffSize.X + 1;
	renderRect.Bottom = buffCoord.Y + buffSize.Y + 1;

	CHAR_INFO* tmp = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* 4);
	tmp[0] = unitData[frame + width + 1];
	tmp[1] = unitData[frame + width - 1];
	tmp[2] = unitData[frame - width + 1];
	tmp[3] = unitData[frame - width - 1];

	if ((frame + 1) % width != 0)
	{
		unitData[frame + width + 1].Char.UnicodeChar = '\\';
		unitData[frame - width + 1].Char.UnicodeChar = '/';
		unitData[frame + width + 1].Attributes = 0x0007 | 0x0008;
		unitData[frame - width + 1].Attributes = 0x0007 | 0x0008;
	}

	if ((frame + 1) % width - 1 != 0)
	{
		unitData[frame - width - 1].Char.UnicodeChar = '\\';
		unitData[frame + width - 1].Char.UnicodeChar = '/';
		unitData[frame + width - 1].Attributes = 0x0007 | 0x0008;
		unitData[frame - width - 1].Attributes = 0x0007 | 0x0008;
	}

	RenderUnitInfo(worldMap[frame]);
	WriteConsoleOutput(hConsole, unitData, buffSize, buffCoord, &renderRect);

	unitData[frame + width + 1] = tmp[0];
	unitData[frame + width - 1] = tmp[1];
	unitData[frame - width + 1] = tmp[2];
	unitData[frame - width - 1] = tmp[3];

	free(tmp);

	return 1;
}

int ConBufferClass::UpdateBorderColour(int playerNum)
{
	for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; ++i)
	{
		if (border[i].Char.UnicodeChar >= 9550 && border[i].Char.UnicodeChar <= 9580)
			border[i].Attributes = playerColour[playerNum];
	}

	RenderBorder();

	return 1;
}

int ConBufferClass::InitializeBorder()
{
	border = (CHAR_INFO *)malloc(sizeof(CHAR_INFO)*SCREEN_HEIGHT*SCREEN_WIDTH);

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
		else if (index < SCREEN_WIDTH || (index > SCREEN_WIDTH * 33 && index < SCREEN_WIDTH * 34 - 1) || (index >(SCREEN_HEIGHT - 1) * SCREEN_WIDTH && index < SCREEN_HEIGHT * SCREEN_WIDTH - 1))
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

CHAR_INFO* ConBufferClass::IntToCharInfo(int num)
{
	int tmp;
	for (int i = 0; i < 4; ++i)
	{
		converted[i].Char.UnicodeChar = 48;
		converted[i].Attributes = 0x0007;
	}
	if (num < 1000)
	{
		converted[0].Char.UnicodeChar = 32;
		if (num < 100)
		{
			converted[1].Char.UnicodeChar = 32;
			if (num < 10)
				converted[2].Char.UnicodeChar = 32;
		}
	}
	if (num > 9999 || num < -999)
		return converted;
	if (num > 0)
	{
		if (num >= 1000)
		{
			tmp = num / 1000;
			num = num - (tmp * 1000);
			tmp += 48;
			converted[0].Char.UnicodeChar = tmp;
		}
		if (num >= 100)
		{
			tmp = num / 100;
			num = num - (tmp * 100);
			tmp += 48;
			converted[1].Char.UnicodeChar = tmp;
		}
		if (num >= 10)
		{
			tmp = num / 10;
			num = num - (tmp * 10);
			tmp += 48;
			converted[2].Char.UnicodeChar = tmp;
		}
		tmp = num + 48;
		converted[3].Char.UnicodeChar = tmp;
	}
	else if (num < 0)
	{
		converted[0].Char.UnicodeChar = 45;
		num = num * (-1);
		if (num >= 100)
		{
			tmp = num / 100;
			num = num - tmp * 100;
			tmp += 48;
			converted[1].Char.UnicodeChar = tmp;
		}
		if (num >= 10)
		{
			tmp = num / 10;
			num = num - tmp * 10;
			tmp += 48;
			converted[2].Char.UnicodeChar = tmp;
		}
		tmp = num + 48;
		converted[3].Char.UnicodeChar = tmp;
	}
	else
		converted[3].Char.UnicodeChar = 48;

	return converted;
}

int ConBufferClass::RenderUnitInfo(EntityClass unit)
{
	SMALL_RECT renderRect;
	renderRect.Left = 59;
	renderRect.Top = 27;
	renderRect.Right = 59 + 16;
	renderRect.Bottom = 28;
	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, unit.unitData.name, strlen(unit.unitData.name)*sizeof(char), wconverted, strlen(unit.unitData.name));
	for (int i = 0, n = strlen(unit.unitData.name); i < n; i++)
	{
		unitName[i].Char.UnicodeChar = unit.unitData.name[i];
		unitName[i].Attributes = 0x007;
	}
	WriteConsoleOutput(hConsole, unitName, { 16, 1 }, { 0, 0 }, &renderRect);

	renderRect.Left = 59;
	renderRect.Top = 28;
	renderRect.Right = 59 + 20;
	renderRect.Bottom = 28 + 8;


	numChar = IntToCharInfo(unit.unitData.hp);
	for (int i = 0; i < 4; ++i)
	{
		unitInfo[9 + i].Char.UnicodeChar = numChar[i].Char.UnicodeChar;
	}
	numChar = IntToCharInfo(unit.unitData.attack);
	for (int i = 0; i < 4; ++i)
	{
		unitInfo[41 + i].Char.UnicodeChar = numChar[i].Char.UnicodeChar;
	}
	numChar = IntToCharInfo(unit.unitData.defense);
	for (int i = 0; i < 4; ++i)
	{
		unitInfo[73 + i].Char.UnicodeChar = numChar[i].Char.UnicodeChar;
	}
	numChar = IntToCharInfo(unit.unitData.actions);
	for (int i = 0; i < 4; ++i)
	{
		unitInfo[105 + i].Char.UnicodeChar = numChar[i].Char.UnicodeChar;
	}

	WriteConsoleOutput(hConsole, unitInfo, { 32, 4 }, { 0, 0 }, &renderRect);

	class_ModelLoader.GetModel(unit.unitData.unitID, 51, 3);

	CHAR_INFO* tmpActionDisplay = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* 32);

	renderRect.Left = SCREEN_WIDTH / 2 - 32 / 2;
	renderRect.Top = 40;
	renderRect.Right = 32 + SCREEN_WIDTH / 2 - 32 / 2;
	renderRect.Bottom = 40 + 1;

	switch (unit.unitData.unitID)
	{
	case 0:
		ConvertString("Q: Spawns a Constructor         ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		renderRect.Top++;
		renderRect.Bottom++;
		ConvertString("W: Spawns a Virus               ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		break;
	case 1:
		ConvertString("Q: Spawns a Core                ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		renderRect.Top++;
		renderRect.Bottom++;
		ConvertString("W: Spawns a Firewall            ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		break;
	case 2:
		ConvertString("This unit will help attack      ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		renderRect.Top++;
		renderRect.Bottom++;
		ConvertString("or defend from your opponents.  ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		break;
	case 3:
		ConvertString("This unit will passivley        ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		renderRect.Top++;
		renderRect.Bottom++;
		ConvertString("produce threads for you to use. ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		break;
	case 4:
		ConvertString("This unit will help slow down   ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		renderRect.Top++;
		renderRect.Bottom++;
		ConvertString("your opponents.                 ", tmpActionDisplay);
		WriteConsoleOutput(hConsole, tmpActionDisplay, { 32, 1 }, { 0, 0 }, &renderRect);
		break;
	}
	
	free(tmpActionDisplay);

	return 1;
}


int ConBufferClass::RenderUnitInfo(CHAR_INFO terrainTile)
{
	//We need to clear the info rendered by unitinfo
	CHAR_INFO* blankChar = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*SCREEN_WIDTH*SCREEN_HEIGHT);
	for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
	{
		blankChar[i].Char.UnicodeChar = 32;
		blankChar[i].Attributes = 0x0007;
	}
	SMALL_RECT renderRect;
	renderRect.Left = 51;
	renderRect.Top = 3;
	renderRect.Right = 51 + 29;
	renderRect.Bottom = 31;

	WriteConsoleOutput(hConsole, blankChar, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0, 0 }, &renderRect);

	renderRect.Left = SCREEN_WIDTH / 2 - 32 / 2;
	renderRect.Top = 40;
	renderRect.Right = 32 + SCREEN_WIDTH / 2 - 32 / 2;
	renderRect.Bottom = 40 + 1;
	
	WriteConsoleOutput(hConsole, blankChar, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0, 0 }, &renderRect);

	free(blankChar);
	return 1;
}

int ConBufferClass::InitializeUnitInfo()
{
	for (int index = 0; index <= 8 * 32; index++)
	{
		unitInfo[index].Char.UnicodeChar = 32;
		unitInfo[index].Attributes = 0x0007;
	}
	for (int index = 0; index < 32 * 24; index++)
	{
		unitModel[index].Char.UnicodeChar = 1;
		unitModel[index].Attributes = 0x0007;
	}
	//Health:
	unitInfo[0].Char.UnicodeChar = 72;
	unitInfo[1].Char.UnicodeChar = 101;
	unitInfo[2].Char.UnicodeChar = 97;
	unitInfo[3].Char.UnicodeChar = 108;
	unitInfo[4].Char.UnicodeChar = 116;
	unitInfo[5].Char.UnicodeChar = 104;
	unitInfo[6].Char.UnicodeChar = 58;
	//Attack:
	unitInfo[32].Char.UnicodeChar = 65;
	unitInfo[33].Char.UnicodeChar = 116;
	unitInfo[34].Char.UnicodeChar = 116;
	unitInfo[35].Char.UnicodeChar = 97;
	unitInfo[36].Char.UnicodeChar = 99;
	unitInfo[37].Char.UnicodeChar = 107;
	unitInfo[38].Char.UnicodeChar = 58;
	//Defense:
	unitInfo[64].Char.UnicodeChar = 68;
	unitInfo[65].Char.UnicodeChar = 101;
	unitInfo[66].Char.UnicodeChar = 102;
	unitInfo[67].Char.UnicodeChar = 110;
	unitInfo[68].Char.UnicodeChar = 115;
	unitInfo[69].Char.UnicodeChar = 101;
	unitInfo[70].Char.UnicodeChar = 58;
	//Actions:
	unitInfo[96].Char.UnicodeChar = 65;
	unitInfo[97].Char.UnicodeChar = 99;
	unitInfo[98].Char.UnicodeChar = 116;
	unitInfo[99].Char.UnicodeChar = 105;
	unitInfo[100].Char.UnicodeChar = 111;
	unitInfo[101].Char.UnicodeChar = 110;
	unitInfo[102].Char.UnicodeChar = 115;
	unitInfo[103].Char.UnicodeChar = 58;

	return 1;
}

int ConBufferClass::RenderExtraInfo(int playerThreads, int turnCounter)
{
	CHAR_INFO* tmp;
	tmp = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* 4);
	SMALL_RECT renderRect;
	renderRect.Left = 56;
	renderRect.Top = 1;
	renderRect.Right = 59;
	renderRect.Bottom = 2;

	tmp = IntToCharInfo(turnCounter);
	WriteConsoleOutput(hConsole, tmp, { 4, 1 }, { 0, 0 }, &renderRect);

	renderRect.Left += 18;
	renderRect.Right += 18;
	tmp = IntToCharInfo(playerThreads);
	WriteConsoleOutput(hConsole, tmp, { 4, 1 }, { 0, 0 }, &renderRect);



	return 1;
}