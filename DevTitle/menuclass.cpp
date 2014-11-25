#include "menuclass.h"

#define SCREEN_HEIGHT 51
#define SCREEN_WIDTH 83

MenuClass::MenuClass(int menuId)
{
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

