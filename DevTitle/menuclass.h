#ifndef MENU_H
#define MENU_H

#include <Windows.h>
#include "inputclass.h"

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


	int Tick();

	int UpdateMenu();

	int RenderStory(int storyId);

	int GetSeed(), GetNumAi(),
		GetAiHandicap(), GetNumOfPlayers();
	bool GetLoadWorld();
private:
	int seed, numAi, aiHandicap, numOfPlayers;
	char buff[64];
	bool loadWorld;

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
	InputClass* _inputClass;
	KEY_EVENT_RECORD input;
};



#endif