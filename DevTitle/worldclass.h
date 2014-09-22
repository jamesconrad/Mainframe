#ifndef WORLDCLASS_H
#define WORLDCLASS_H

#include "conbufferclass.h"
#include "unitinfoclass.h"
#include "entityclass.h"
#include "inputclass.h"
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

	int SpawnUnit(int id, int playerId, int index);

private:
	int frame;
	int height, width;
	int numOfUnits;
	
	CHAR_INFO *worldMap;
	CHAR_INFO *unitMap;

	UnitData *unitPositionIndex;

	UnitInfoClass class_UnitInfo;
	ConBufferClass class_ConBuffer;
	InputClass class_InputClass;
	std::vector<EntityClass> class_EntityArray;
};
#endif