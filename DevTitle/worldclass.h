#ifndef WORLDCLASS_H
#define WORLDCLASS_H

#include "conbufferclass.h"
#include "unitinfoclass.h"
#include "entityclass.h"
#include "inputclass.h"
#include "modelloader.h"
#include "audioclass.h"
#include <vector>

class WorldClass
{
public:
	WorldClass();
	WorldClass(const WorldClass&);
	~WorldClass();

	CHAR_INFO* GetMap();

	COORD ConvertIndex(int);
	int ConvertCoord(COORD);

	int Initialize(CHAR_INFO*, int, int, int);

	int ChangeFrame(int);
	int GetFrame();

	int UpdateTile(int index, CHAR_INFO);

	int Render();
	int Tick();

	int SpawnUnit(int id, int index);
	int UpdateHealthBg(int index);
	
	int PassCurrentPlayerThreads();
	int PassTurns();

	int NextTurn();
	int CheckInput();


private:
	int frame,
		height, width,
		numOfUnits,
		numOfPlayers,
		currentTurn,
		playerColour[7],
		playerThreads[7],
		turnCounter;
	bool moveUnit, 
		attackUnit, 
		frameChanged;

	CHAR_INFO *worldMap;
	CHAR_INFO *unitMap;

	UnitData *unitPositionIndex;

	KEY_EVENT_RECORD keyPress, prevKeyPress;

	HANDLE inputThread;

	AudioClass class_AudioClass;
	UnitInfoClass class_UnitInfo;
	ConBufferClass class_ConBuffer;
	InputClass class_InputClass;
	std::vector<EntityClass> class_EntityArray;
};
#endif