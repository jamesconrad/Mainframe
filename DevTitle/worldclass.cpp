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
	WorldClass::class_ConBuffer.Initialize();
	WorldClass::class_UnitInfo.Initialize();
	WorldClass::class_InputClass.Initialize();
	WorldClass::worldMap = generation;
	WorldClass::unitMap = generation; // (CHAR_INFO*)malloc(sizeof(CHAR_INFO*)*WorldClass::width*WorldClass::height);
	for (int i = 0; i < WorldClass::width*WorldClass::height; i++)
	{
		//unitMap[i] = generation[i];
	}
	WorldClass::frame = frame;
	WorldClass::height = height;
	WorldClass::width = width;
	
	WorldClass::class_EntityArray = (EntityClass*)malloc(sizeof(EntityClass*)*WorldClass::numOfUnits);

	return 1;
}

int WorldClass::UpdateTile(int x, int y, int newTile)
{
	WorldClass::worldMap[x].Char.AsciiChar = newTile;
	return 1;
}

int WorldClass::Render()
{
	//class_ConBuffer.ClearConsole(class_ConBuffer.hConsole);
		
	//Temp
	COORD frameCoords = WorldClass::ConvertIndex(WorldClass::frame);
	frameCoords.X++;
	frameCoords.Y++;
	SetConsoleCursorPosition(class_ConBuffer.hConsole, frameCoords);

	//Setup the unitMap
	for (int i = 0; i < numOfUnits; i++)
	{
		unitMap[WorldClass::class_EntityArray[numOfUnits].unitData.position] = WorldClass::class_EntityArray[numOfUnits].unitData.charInfo;
	}

	WorldClass::class_ConBuffer.OutputScreen(WorldClass::worldMap, WorldClass::unitMap, WorldClass::height, WorldClass::width, { 0, 0 });

	return 1;
}

int WorldClass::GetFrame()
{
	return WorldClass::frame;
}

int WorldClass::ChangeFrame(int newFrame)
{
	WorldClass::frame = newFrame;
	return 1;
}

COORD WorldClass::ConvertIndex(int index)
{
	COORD indexCoord;
	indexCoord.Y = index / WorldClass::width;
	indexCoord.X = index % WorldClass::width;

	return indexCoord;
}

int WorldClass::ConvertCoord(COORD indexCoord)
{
	int index;
	index = indexCoord.Y * WorldClass::width;
	index += indexCoord.X;

	return index;
}

int WorldClass::SpawnUnit(int id, int playerId, int index)
{
	UnitData unitData = class_UnitInfo.unit[id];

	WorldClass::class_EntityArray = (EntityClass *)malloc(sizeof(EntityClass*)*WorldClass::numOfUnits);

	unitData.playerID = playerId;
	unitData.position = index;
	
	WorldClass::class_EntityArray[numOfUnits].unitData = unitData;
	WorldClass::class_EntityArray[numOfUnits].unitData.charInfo.Attributes = PLAYER_COLOUR_1;

	WorldClass::unitMap[WorldClass::class_EntityArray[numOfUnits].unitData.position] = WorldClass::class_EntityArray[numOfUnits].unitData.charInfo;

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