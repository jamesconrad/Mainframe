#include "menuclass.h"
#include <ctime>
#include <iostream>

#define SCREEN_HEIGHT 51
#define SCREEN_WIDTH 83

MenuClass::MenuClass(int menuId)
{
	srand(time(NULL));
	seed = rand()*rand();
	srand(seed);

	numAi = 1;
	aiHandicap = 0;
	numOfPlayers = 2;
	char buff[64] = "ERROR";

	loadWorld = false;

	this->menuId = menuId;
	hConsole = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	isInMenu = true;
	SMALL_RECT screenSize;
	screenSize.Left = 0;
	screenSize.Right = SCREEN_WIDTH - 1;
	screenSize.Top = 0;
	screenSize.Bottom = SCREEN_HEIGHT - 1;

	SetConsoleScreenBufferSize(hConsole, { SCREEN_WIDTH, SCREEN_HEIGHT });
	SetConsoleWindowInfo(hConsole, true, &screenSize);

	SetConsoleTitle(L"Mainframe");

	_inputClass = new InputClass();
	_inputClass->Initialize();

	SetNumOptions(4);
	SetOptionText(0, "Singleplayer");
	SetOptionText(1, "Multiplayer");
	SetOptionText(2, "Help");
	SetOptionText(3, "Quit");
	OptionDown();
	OptionUp();
}

void MenuClass::NewId(int id)
{
	menuId = id;
}

int MenuClass::GetId()
{
	return menuId;
}

int MenuClass::ClearScreen()
{
	CHAR_INFO* blank = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*SCREEN_HEIGHT*SCREEN_WIDTH);
	for (int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++)
	{
		blank[i].Char.UnicodeChar = 32;
		blank[i].Attributes = 0x007;
	}

	SMALL_RECT* renderRect = new SMALL_RECT();
	renderRect->Left = 0;
	renderRect->Right = SCREEN_WIDTH - 1;
	renderRect->Top = 0;
	renderRect->Bottom = SCREEN_HEIGHT - 1;

	WriteConsoleOutput(hConsole, blank, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0, 0 }, renderRect);

	free(renderRect);
	free(blank);

	return 1;
}

int MenuClass::ConvertString(const char * text, CHAR_INFO * result)
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

int MenuClass::OptionDown()
{
	if (cursor < numOfOptions - 1)
	{
		for (int i = 0; i < menu[cursor].len; i++)
			menu[cursor].text[i].Attributes = 0x007;

		cursor++;

		for (int i = 0; i < menu[cursor].len; i++)
			menu[cursor].text[i].Attributes = 0x002 | 0x008;
	}
	else
		return 0;



	return 1;
}

int MenuClass::OptionUp()
{
	if (cursor > 0)
	{
		for (int i = 0; i < menu[cursor].len; i++)
			menu[cursor].text[i].Attributes = 0x007;

		cursor--;

		for (int i = 0; i < menu[cursor].len; i++)
			menu[cursor].text[i].Attributes = 0x002 | 0x008;

	}
	else
		return 0;

	return 1;
}

int MenuClass::SetNumOptions(int num)
{
	numOfOptions = num;
	free(menu);
	menu = (MenuObject*)malloc(sizeof(MenuObject)*numOfOptions);
	return 1;
}

int MenuClass::SetOptionText(int optionNum, const char* text)
{
	menu[optionNum].text = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*strlen(text));
	ConvertString(text, menu[optionNum].text);
	menu[optionNum].len = strlen(text);
	return 1;
}

int MenuClass::ClearOptionText(int optionNum)
{
	free(menu[optionNum].text);

	return 1;
}

int MenuClass::Render()
{
	SMALL_RECT renderRect;
	
	for (int i = 0; i < titleHeight; i++)
	{
		//WriteConsoleOutput(hConsole, title[i], { 0, 0 }, { titleWidth, titleHeight }, &renderRect);
	}

	for (int i = 0; i < numOfOptions; i++)
	{
		renderRect.Top = titleHeight + 2 + i;
		renderRect.Bottom = titleHeight + 3 + i;
		renderRect.Left = SCREEN_WIDTH / 2 - menu[i].len / 2;
		renderRect.Right = SCREEN_WIDTH / 2 + menu[i].len / 2 + i;

		WriteConsoleOutput(hConsole, menu[i].text, { menu[i].len, 1 }, { 0, 0 }, &renderRect);
	}

	return 1;
}

int MenuClass::GetActiveOption()
{
	return cursor;
}

bool MenuClass::MenuActive()
{
	return isInMenu;
}

int MenuClass::GetSeed()
{
	return seed;
}
int MenuClass::GetNumAi()
{
	return numAi;
}
int MenuClass::GetAiHandicap()
{
	return aiHandicap;
}
int MenuClass::GetNumOfPlayers()
{
	return numOfPlayers;
}
bool MenuClass::GetLoadWorld()
{
	return loadWorld;
}

int MenuClass::Tick()
{
	input = _inputClass->GetKeypress();
	UpdateMenu();
	Render();

	return 1;
}

int MenuClass::UpdateMenu()
{
	
	if (input.wVirtualKeyCode == VK_UP && input.bKeyDown == true)
		OptionUp();
	if (input.wVirtualKeyCode == VK_DOWN && input.bKeyDown == true)
		OptionDown();
	//numAi setting
	if (input.wVirtualKeyCode == VK_RIGHT && input.bKeyDown == true && cursor == 3 && menuId == 2)
	{
		if (numAi < 5)
		{
			numAi++;
			numOfPlayers++;
		}
		_itoa(numAi, buff, 10);
		SetOptionText(3, buff);
		ClearScreen();
		OptionUp();
		OptionDown();
	}
	else if (input.wVirtualKeyCode == VK_LEFT && input.bKeyDown == true && cursor == 3 && menuId == 2)
	{
		if (numAi > 1)
		{
			numAi--;
			numOfPlayers--;
		}
		_itoa(numAi, buff, 10);
		SetOptionText(3, buff);
		ClearScreen();
		OptionUp();
		OptionDown();
	}
	//aiHandicap setting
	else if (input.wVirtualKeyCode == VK_RIGHT && input.bKeyDown == true && cursor == 5 && menuId == 2)
	{
		aiHandicap++;
		_itoa(aiHandicap, buff, 10);
		SetOptionText(5, buff);;
		ClearScreen();
		OptionUp();
		OptionDown();
	}
	else if (input.wVirtualKeyCode == VK_LEFT && input.bKeyDown == true && cursor == 5 && menuId == 2)
	{
		aiHandicap--;
		_itoa(aiHandicap, buff, 10);
		SetOptionText(5, buff);
		ClearScreen();
		OptionUp();
		OptionDown();
	}

	if (input.wVirtualKeyCode == VK_RETURN && input.bKeyDown == true && menuId == 1)
	{
		if (cursor == 0)
		{
			ClearScreen();
			SetNumOptions(8);

			SetOptionText(0, "Seed:");
			_itoa(time(NULL), buff, 10);
			SetOptionText(1, buff); // Possible change here
			SetOptionText(2, "Number of AI opponents");
			_itoa(numAi, buff, 10);
			SetOptionText(3, buff);
			SetOptionText(4, "AI Handicap:");
			_itoa(aiHandicap, buff, 10);
			SetOptionText(5, buff); //Possible change here
			SetOptionText(6, "Load Game"); //Possible change here
			SetOptionText(7, "Start Game");
			NewId(2);

			//Done. Now cycle selections
			OptionDown();
			OptionUp();
		}
		else if (cursor == 1)
		{
			ClearScreen();
			SetNumOptions(6);

			SetOptionText(0, "Seed:");
			SetOptionText(1, "seed"); // Possible change here
			SetOptionText(2, "Number of Players");
			SetOptionText(3, "0");
			SetOptionText(4, "Load Game"); //Possible change here
			SetOptionText(5, "Start Game");
			NewId(3);

			//Done. Now cycle selections
			OptionDown();
			OptionUp();
		}
		else if (cursor == 2)
		{
			menuId = 5;
			ClearScreen();
			SetNumOptions(13);
			SetOptionText(0, "GAMEPLAY");
			SetOptionText(1, "Move your units around the world");
			SetOptionText(2, "in an attempt to eliminate your opponents.");
			SetOptionText(3, "");
			SetOptionText(4, "CONTROLS");
			SetOptionText(5, "Cursor Movement:     ARROW KEYS");
			SetOptionText(6, "Attack:           A + ARROW KEY");
			SetOptionText(7, "Move:             M + ARROW KEY");
			SetOptionText(8, "Ability 1:        Q + ARROW KEY");
			SetOptionText(9, "Ability 2:        W + ARROW KEY");
			SetOptionText(10, "Quit:                       ESC");
			SetOptionText(11, "");
			SetOptionText(12, "Back");
			cursor = 12;
			OptionUp();
			OptionDown();
		}
		else if (cursor == 3)
			exit(1);
		//numAi setting
	}
	else if (input.wVirtualKeyCode == VK_RETURN && input.bKeyDown == true && menuId == 2)
	{
		if (input.wVirtualKeyCode == VK_RETURN && input.bKeyDown == true && cursor == 7)
		{
			//LETS PLAY -> Singleplayer
			isInMenu = false;
			ClearScreen();

		}
		else if (input.wVirtualKeyCode == VK_RETURN && input.bKeyDown == true && cursor == 6)
		{
			
			if (FILE *file = fopen("misc", "r"))
			{
				fclose(file);
				isInMenu = false;
				loadWorld = true;
			}
			else
				SetOptionText(6, "No game data to load!");
		}
	}
	
	else if (input.wVirtualKeyCode == VK_RETURN && input.bKeyDown == true && menuId == 5)
	{
		cursor = 0;
		SetNumOptions(4);
		SetOptionText(0, "Singleplayer");
		SetOptionText(1, "Multiplayer");
		SetOptionText(2, "Help");
		SetOptionText(3, "Quit");
		OptionDown();
		OptionUp();
		ClearScreen();
		menuId = 1;
		
	}
}