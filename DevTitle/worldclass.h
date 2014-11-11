#ifndef WORLDCLASS_H
#define WORLDCLASS_H

#include "conbufferclass.h"
#include "unitinfoclass.h"
#include "entityclass.h"
#include "inputclass.h"
#include "modelloader.h"
#include "audioclass.h"
#include "aiclass.h"
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
	int Update(int index);
	int Tick();

	int SpawnUnit(int id, int index);
	int UpdateHealthBg(int index);
	int UpdateUnitMap();
	
	int PassCurrentPlayerThreads();
	int PassTurns();

	int NextTurn();
	int CheckInput();


private:
	int frame, height, width,
		numOfUnits, numOfPlayers, currentTurn,
		playerColour[7], playerThreads[7], turnCounter;

	bool moveUnit, attackUnit, frameChanged;

	CHAR_INFO *worldMap;
	CHAR_INFO *unitMap;

	UnitData *unitPositionIndex;

	KEY_EVENT_RECORD keyPress, prevKeyPress;

	HANDLE inputThread;

	AudioClass _audioClass;
	AudioClass wavPlayer;
	UnitInfoClass _unitInfo;
	ConBufferClass _conBuffer;
	InputClass _inputClass;
	std::vector<EntityClass> _entityArray;
};
#endif