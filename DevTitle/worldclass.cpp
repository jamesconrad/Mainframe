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
	return worldMap;
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

	class_UnitInfo.Initialize();
	class_InputClass.Initialize();

	return 1;
}

int WorldClass::UpdateTile(int index, CHAR_INFO newTile)
{
	worldMap[index] = newTile;
	return 1;
}

int WorldClass::Render()
{
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
	
	unitData.playerID = playerId;
	unitData.position = index;

	EntityClass class_TempEntity;

	class_TempEntity.unitData = unitData;
	class_TempEntity.unitData.charInfo.Attributes = PLAYER_COLOUR_2;
	
	class_EntityArray.push_back(class_TempEntity);
	class_EntityArray[numOfUnits].unitData = class_TempEntity.unitData;
	unitMap[unitData.position] = class_TempEntity.unitData.charInfo;
			
	numOfUnits++;
	return numOfUnits;
}

int WorldClass::Tick()
{
	KEY_EVENT_RECORD keyPress;
	keyPress = class_InputClass.GetKeypress();
	bool collision = false;
	if (keyPress.wVirtualKeyCode == VK_UP && keyPress.bKeyDown == true)
	{
		if (frame - width >= 0)
		{
			frame -= width;
		}
	}
	else if (keyPress.wVirtualKeyCode == VK_DOWN && keyPress.bKeyDown == true)
	{
		if (frame + width < height * width)
		{
			frame += width;
		}
	}
	else if (keyPress.wVirtualKeyCode == VK_RIGHT && keyPress.bKeyDown == true)
	{
		if (frame % width != width - 1)
		{
			frame++;
		}
	}
	else if (keyPress.wVirtualKeyCode == VK_LEFT && keyPress.bKeyDown == true)
	{
		if (frame % width != 0)
		{
			frame--;
		}
	}
	else if (keyPress.wVirtualKeyCode == 0x2D && keyPress.bKeyDown == true) //Insert
	{
		SpawnUnit(7, 0, frame);
	}
	//Need to check for colision with other entitys and map edges
	else if (keyPress.wVirtualKeyCode == 0x57 && keyPress.bKeyDown == true) //W
	{
		for (int i = 0; i < numOfUnits; i++)
		{
			if (class_EntityArray[i].unitData.position == frame)
			{
				for (int j = 0; j < numOfUnits; j++)
				{
					if (class_EntityArray[j].unitData.position != class_EntityArray[i].unitData.position - width && class_EntityArray[i].unitData.position - width >= 0)
					{
						unitMap[class_EntityArray[i].unitData.position] = worldMap[class_EntityArray[i].unitData.position];
						class_EntityArray[i].unitData.position -= width;
						unitMap[class_EntityArray[i].unitData.position] = class_EntityArray[i].unitData.charInfo;
						break;
					}
				}
			}
		}
	}
	else if (keyPress.wVirtualKeyCode == 0x53 && keyPress.bKeyDown == true) //S
	{
		for (int i = 0; i < numOfUnits; i++)
		{
			if (class_EntityArray[i].unitData.position == frame)
			{
				for (int j = 0; j < numOfUnits; j++)
				{
					if (class_EntityArray[j].unitData.position != class_EntityArray[i].unitData.position + width &&  class_EntityArray[i].unitData.position + width < width*height)
					{
						unitMap[class_EntityArray[i].unitData.position] = worldMap[class_EntityArray[i].unitData.position];
						class_EntityArray[i].unitData.position += width;
						unitMap[class_EntityArray[i].unitData.position] = class_EntityArray[i].unitData.charInfo;
						break;
					}
				}
			}
		}
	}
	else if (keyPress.wVirtualKeyCode == 0x41 && keyPress.bKeyDown == true) //A
	{
		for (int i = 0; i < numOfUnits; i++)
		{
			if (class_EntityArray[i].unitData.position == frame)
			{
				for (int j = 0; j < numOfUnits; j++)
				{
					if (class_EntityArray[j].unitData.position != class_EntityArray[i].unitData.position - 1 && class_EntityArray[i].unitData.position % width != 0)
					{
						unitMap[class_EntityArray[i].unitData.position] = worldMap[class_EntityArray[i].unitData.position];
						class_EntityArray[i].unitData.position -= 1;
						unitMap[class_EntityArray[i].unitData.position] = class_EntityArray[i].unitData.charInfo;
						break;
					}
				}
			}
		}
	}
	else if (keyPress.wVirtualKeyCode == 0x44 && keyPress.bKeyDown == true) //D
	{
		for (int i = 0; i < numOfUnits; i++)
		{
			if (class_EntityArray[i].unitData.position == frame)
			{
				for (int j = 0; j < numOfUnits; j++)
				{
					if (class_EntityArray[j].unitData.position != class_EntityArray[i].unitData.position + 1 && class_EntityArray[i].unitData.position % width != width - 1)
					{
						unitMap[class_EntityArray[i].unitData.position] = worldMap[class_EntityArray[i].unitData.position];
						class_EntityArray[i].unitData.position += 1;
						unitMap[class_EntityArray[i].unitData.position] = class_EntityArray[i].unitData.charInfo;
						break;
					}
				}
			}
		}
	}
	WorldClass::Render();
	return 1;
}