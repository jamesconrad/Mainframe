#ifndef WORLDCLASS_H
#define WORLDCLASS_H

#include "conbufferclass.h"
#include "unitinfoclass.h"
#include "entityclass.h"
#include "inputclass.h"
#include <vector>

class WorldClass {
private:
	int frame;
	CHAR_INFO* worldMap;
	CHAR_INFO* unitMap;
	int height, width;

	int numOfUnits;
	UnitData * unitPositionIndex;
	UnitInfoClass class_UnitInfo;
	ConBufferClass class_ConBuffer;
	InputClass class_InputClass;
	std::vector<EntityClass> class_EntityArray;
	//EntityClass * class_EntityArray;
public:
	WorldClass();
	WorldClass(const WorldClass&);
	~WorldClass();

	CHAR_INFO* GetMap();
	COORD ConvertIndex(int);
	int ConvertCoord(COORD);
	int Initialize(CHAR_INFO*, int, int, int);
	int ChangeFrame(int);
	int UpdateTile(int, int, int);
	int Render();
	int GetFrame();
	int SpawnUnit(int id, int playerId, int index);
	int Tick();
	int SetUnitData();
};
#endif