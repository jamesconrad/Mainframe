#ifndef MENU_H
#define MENU_H

#include <Windows.h>

class MenuClass
{
public:
	MenuClass(int menuId);

	int ConvertString(const char * text, CHAR_INFO * result);

	int OptionUp();
	int OptionDown();

	int SetNumOptions(int num);
	int SetOptionText(int optionNum, const char * text);
	
	int ClearOptionText(int optionNum);

	int Render();

	bool MenuActive();

	int GetActiveOption();

	int ClearScreen();

	void NewId(int id);
	int GetId();

private:
	HANDLE hConsole;
	int numOfOptions, cursor, menuId;
	bool isInMenu;
	
	int titleHeight, titleWidth;
	CHAR_INFO title[1][1];
	struct MenuObject
	{
		int len;
		CHAR_INFO * text;
	};
	
	MenuObject* menu;
};



#endif