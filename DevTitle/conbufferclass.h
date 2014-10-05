#ifndef CONBUFFERCLASS_H
#define CONBUFFERCLASS_H

#include <Windows.h>
#include "entityclass.h"
#include "modelloader.h"

class ConBufferClass
{
public:
	HANDLE hConsole;

	int playerColour[7];

	ConBufferClass();
	ConBufferClass(const ConBufferClass&);
	~ConBufferClass();
	int Initialize();

	int OutputScreen(CHAR_INFO*, CHAR_INFO*, int, int, COORD, COORD, EntityClass selectedUnit);
	int OutputScreen(CHAR_INFO*, CHAR_INFO*, int, int, COORD, COORD, int frame);
	int RenderExtraInfo(int playerThreads, int turnCounter);

	int ClearConsole(HANDLE, COORD);
	int UpdateBorderColour(int playerNum);
private:
	COORD beginCoords;
	DWORD nWritten;

	ModelLoaderClass class_ModelLoader;

	CHAR_INFO *border,
		*unitInfo,
		*unitModel,
		*unitActions,
		*converted,
		*numChar;

	int RenderBorder();
	int RenderUnitInfo(EntityClass unit);
	int RenderUnitInfo(CHAR_INFO terrainTile);
	int InitializeBorder();
	int InitializeUnitInfo();

	CHAR_INFO* IntToCharInfo(int num);
};

#endif