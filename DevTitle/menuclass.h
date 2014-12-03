#ifndef MENU_H
#define MENU_H
//MenuClass, much like WorldClass needs to have control passed to it.
#include <Windows.h>
#include "inputclass.h"
#include "modelloader.h"

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
	ModelLoaderClass _modelLoader;
	KEY_EVENT_RECORD input;
};



#endif