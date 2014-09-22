#include "worldclass.h"
#include <iostream>

#define PLAYER_COLOUR_0 0x0000 | 0x0008
#define PLAYER_COLOUR_1 0x0001 | 0x0008
#define PLAYER_COLOUR_2 0x0002 | 0x0008
#define PLAYER_COLOUR_3 0x0003 | 0x0008
#define PLAYER_COLOUR_4 0x0004 | 0x0008
#define PLAYER_COLOUR_5 0x0005 | 0x0008
#define PLAYER_COLOUR_6 0x0006 | 0x0008
#define PLAYER_COLOUR_7 0x0007 | 0x0008



WorldClass::WorldClass()
{

}
WorldClass::WorldClass(const WorldClass&)
{

}

WorldClass::~WorldClass()
{

}

CHAR_INFO* WorldClass::GetMap()
{
	return WorldClass::worldMap;
}
int WorldClass::Initialize(CHAR_INFO* generation, int frame, int width, int height)
{
	worldMap = generation;

	class_ConBuffer.Initialize();
	
	unitMap = (CHAR_INFO*)malloc(sizeof(CHAR_INFO*)*width*height);
	
	memcpy(unitMap, worldMap, sizeof(CHAR_INFO)*width*height);
	WorldClass::frame = frame;
	WorldClass::height = height;
	WorldClass::width = width;
	numOfUnits = 0;
	
	//class_EntityArray = (EntityClass*)malloc(sizeof(EntityClass*)*WorldClass::numOfUnits);

	class_UnitInfo.Initialize();
	class_InputClass.Initialize();

	return 1;
}

int WorldClass::UpdateTile(int x, int y, int newTile)
{
	worldMap[x].Char.AsciiChar = newTile;
	return 1;
}

int WorldClass::Render()
{
	//class_ConBuffer.ClearConsole(class_ConBuffer.hConsole);
		
	//Temp
	COORD frameCoords = ConvertIndex(frame);
	frameCoords.X++;
	frameCoords.Y++;
	SetConsoleCursorPosition(class_ConBuffer.hConsole, frameCoords);

	class_ConBuffer.OutputScreen(worldMap, unitMap, height, width, { 0, 0 }, frameCoords);

	return 1;
}

int WorldClass::GetFrame()
{
	return frame;
}

int WorldClass::ChangeFrame(int newFrame)
{
	frame = newFrame;
	return 1;
}

COORD WorldClass::ConvertIndex(int index)
{
	COORD indexCoord;
	indexCoord.Y = index / width;
	indexCoord.X = index % width;

	return indexCoord;
}

int WorldClass::ConvertCoord(COORD indexCoord)
{
	int index;
	index = indexCoord.Y * width;
	index += indexCoord.X;

	return index;
}

int WorldClass::SpawnUnit(int id, int playerId, int index)
{
	UnitData unitData = class_UnitInfo.unit[id];
	//class_EntityArray = (EntityClass *)malloc(sizeof(EntityClass)*(numOfUnits+1));
	
	unitData.playerID = playerId;
	unitData.position = index;

	EntityClass class_TempEntity;

	class_TempEntity.unitData = unitData;
	class_TempEntity.unitData.charInfo.Attributes = PLAYER_COLOUR_2;
	
	class_EntityArray.push_back(class_TempEntity);
	class_EntityArray[numOfUnits].unitData = unitData;
	unitMap[unitData.position].Char.UnicodeChar = class_TempEntity.unitData.charInfo.Char.UnicodeChar;
	unitMap[unitData.position].Attributes = class_TempEntity.unitData.charInfo.Attributes;
		
	numOfUnits++;
	return numOfUnits;
}

int WorldClass::Tick()
{
	KEY_EVENT_RECORD keyPress;
	keyPress = class_InputClass.GetKeypress();
	keyPress.bKeyDown == true;
	keyPress.wVirtualKeyCode == VK_DOWN;
	keyPress.dwControlKeyState == SHIFT_PRESSED;
	if (keyPress.wVirtualKeyCode == VK_UP && keyPress.bKeyDown == true)
	{
		if (WorldClass::frame - WorldClass::width > 0)
		{
			WorldClass::frame -= WorldClass::width;
		}
	}
	if (keyPress.wVirtualKeyCode == VK_DOWN && keyPress.bKeyDown == true)
	{
		if (WorldClass::frame + WorldClass::width < WorldClass::height * WorldClass::width)
		{
			WorldClass::frame += WorldClass::width;
		}
	}
	if (keyPress.wVirtualKeyCode == VK_RIGHT && keyPress.bKeyDown == true)
	{
		if (WorldClass::frame % WorldClass::width != WorldClass::width - 1)
		{
			WorldClass::frame++;
		}
	}
	if (keyPress.wVirtualKeyCode == VK_LEFT && keyPress.bKeyDown == true)
	{
		if (WorldClass::frame % WorldClass::width != 0)
		{
			WorldClass::frame--;
		}
	}
	if (keyPress.wVirtualKeyCode == 0x53 && keyPress.bKeyDown == true) //S
	{
		WorldClass::SpawnUnit(7, 0, WorldClass::frame);
	}
	WorldClass::Render();
	
	return 1;
}

int WorldClass::SetUnitData()
{


	return 1;
}