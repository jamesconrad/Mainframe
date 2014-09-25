#include "worldclass.h"
#include <iostream>

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

	playerColour[0] = 0x0001 | 0x0008;
	playerColour[1] = 0x0002 | 0x0008;
	playerColour[2] = 0x0003 | 0x0008;
	playerColour[3] = 0x0004 | 0x0008;
	playerColour[4] = 0x0005 | 0x0008;
	playerColour[5] = 0x0006 | 0x0008;
	playerColour[6] = 0x0007 | 0x0008;

	currentTurn = 1;
	numOfPlayers = 6;

	prevKeyPress = class_InputClass.GetKeypress();
	keyPress = class_InputClass.GetKeypress();

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

int WorldClass::SpawnUnit(int id, int index)
{
	UnitData unitData = class_UnitInfo.unit[id];

	unitData.playerID = currentTurn;
	unitData.position = index;

	EntityClass class_TempEntity;

	class_TempEntity.unitData = unitData;
	class_TempEntity.unitData.charInfo.Attributes = playerColour[currentTurn];

	class_EntityArray.push_back(class_TempEntity);
	class_EntityArray[numOfUnits].unitData = class_TempEntity.unitData;
	unitMap[unitData.position] = class_TempEntity.unitData.charInfo;

	numOfUnits++;
	return numOfUnits;
}

int WorldClass::NextTurn()
{
	if (numOfPlayers - 1 <= currentTurn)
	{
		currentTurn = 0;
		++turnCounter;
	}
	else
		++currentTurn;

	class_ConBuffer.UpdateBorderColour(currentTurn);

	return 1;
}

int WorldClass::Tick()
{
	keyPress = class_InputClass.GetKeypress();
	WorldClass::CheckInput();
	WorldClass::Render();
	return 1;
}

int WorldClass::CheckInput()
{
	bool collision = false;
	if (keyPress.wVirtualKeyCode == VK_SPACE && keyPress.bKeyDown == true)
	{
		WorldClass::NextTurn();
		Sleep(1000);
	}
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
		SpawnUnit(7, frame);
	}
	//else if (keyPress.wVirtualKeyCode == 0x4D && keyPress.bKeyDown == true)
	//{
		//keyPress = class_InputClass.GetKeypressWait();
		//Need to check for colision with other entitys and map edges
		if (keyPress.wVirtualKeyCode == 0x57 && keyPress.bKeyDown == true) //W
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (class_EntityArray[i].unitData.position == frame)
				{
					for (int j = 0; j < numOfUnits; j++)
					{
						if (class_EntityArray[j].unitData.position != class_EntityArray[i].unitData.position - width)
						{
							collision = true;
						}
					}
					if (class_EntityArray[i].unitData.position - width >= 0 && !collision && class_EntityArray[i].unitData.actions > 0 && class_EntityArray[i].unitData.playerID == currentTurn)
					{
						unitMap[class_EntityArray[i].unitData.position] = worldMap[class_EntityArray[i].unitData.position];
						class_EntityArray[i].unitData.position -= width;
						unitMap[class_EntityArray[i].unitData.position] = class_EntityArray[i].unitData.charInfo;
						--class_EntityArray[i].unitData.actions;
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
						if (class_EntityArray[j].unitData.position != class_EntityArray[i].unitData.position + width)
						{
							collision = true;
						}
					}
					if (class_EntityArray[i].unitData.position + width < width*height && !collision && class_EntityArray[i].unitData.actions > 0 && class_EntityArray[i].unitData.playerID == currentTurn)
					{
						unitMap[class_EntityArray[i].unitData.position] = worldMap[class_EntityArray[i].unitData.position];
						class_EntityArray[i].unitData.position += width;
						unitMap[class_EntityArray[i].unitData.position] = class_EntityArray[i].unitData.charInfo;
						--class_EntityArray[i].unitData.actions;
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
						if (class_EntityArray[j].unitData.position != class_EntityArray[i].unitData.position - 1)
						{
							collision = true;
						}
					}
					if (class_EntityArray[i].unitData.position % width != 0 && !collision && class_EntityArray[i].unitData.actions > 0 && class_EntityArray[i].unitData.playerID == currentTurn)
					{
						unitMap[class_EntityArray[i].unitData.position] = worldMap[class_EntityArray[i].unitData.position];
						class_EntityArray[i].unitData.position -= 1;
						unitMap[class_EntityArray[i].unitData.position] = class_EntityArray[i].unitData.charInfo;
						--class_EntityArray[i].unitData.actions;
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
						if (class_EntityArray[j].unitData.position != class_EntityArray[i].unitData.position + 1)
						{
							collision = true;
						}
					}
					if (class_EntityArray[i].unitData.position % width != width - 1 && !collision && class_EntityArray[i].unitData.actions > 0 && class_EntityArray[i].unitData.playerID == currentTurn)
					{
						unitMap[class_EntityArray[i].unitData.position] = worldMap[class_EntityArray[i].unitData.position];
						class_EntityArray[i].unitData.position += 1;
						unitMap[class_EntityArray[i].unitData.position] = class_EntityArray[i].unitData.charInfo;
						--class_EntityArray[i].unitData.actions;
					}
				}
			}
		}
	//}

	return 1;
}