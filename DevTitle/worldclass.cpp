#include "worldclass.h"
#include <iostream>
#pragma comment (lib,"Winmm.lib")

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

	moveUnit = false;
	attackUnit = false;
	frameChanged = true;

	class_ConBuffer.Initialize();

	unitMap = (CHAR_INFO*)malloc(sizeof(CHAR_INFO*)*width*height);

	memcpy(unitMap, worldMap, sizeof(CHAR_INFO)*width*height);
	WorldClass::frame = frame;
	WorldClass::height = height;
	WorldClass::width = width;
	numOfUnits = 0;

	class_UnitInfo.Initialize();
	class_InputClass.Initialize();

	class_AudioClass.Load(L"DST-3rdBallad.mp3");
	class_AudioClass.Play();

	playerColour[0] = 0x0001 | 0x0008;
	playerColour[1] = 0x0002 | 0x0008;
	playerColour[2] = 0x0003 | 0x0008;
	playerColour[3] = 0x0004 | 0x0008;
	playerColour[4] = 0x0005 | 0x0008;
	playerColour[5] = 0x0006 | 0x0008;

	currentTurn = 0;
	numOfPlayers = 5;

	prevKeyPress = class_InputClass.GetKeypress();
	keyPress = class_InputClass.GetKeypress();

	for (int i = 0; i < numOfPlayers; ++i)
		playerThreads[i] = 3;

	for (int i = 0; i <= numOfPlayers; ++i)
	{
		SpawnUnit(0, rand() % (width*height));
		++currentTurn;
	}
	currentTurn = 0;
	class_ConBuffer.UpdateBorderColour(currentTurn);
	turnCounter = 1;

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
	if (frameChanged)
	{
		SetConsoleCursorPosition(class_ConBuffer.hConsole, frameCoords);
		frameChanged = false;
	}

	for (int i = 0; i < numOfUnits; ++i)
	{
		if (frame == class_EntityArray[i].unitData.position)
			class_ConBuffer.OutputScreen(unitMap, height, width, { 0, 0 }, frame, class_EntityArray[i]);

	}
	class_ConBuffer.OutputScreen(worldMap, unitMap, height, width, { 0, 0 }, frame);
	class_ConBuffer.RenderExtraInfo(playerThreads[currentTurn], turnCounter);

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
	class_EntityArray[numOfUnits].Initialize(width, height, worldMap, unitMap);
	class_EntityArray[numOfUnits].unitData = class_TempEntity.unitData;
	unitMap[unitData.position] = class_TempEntity.unitData.charInfo;

	//Set actions to 0 for this turn only
	class_EntityArray[numOfUnits].unitData.actions = 0;


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

	for (int i = 0; i < numOfUnits; ++i)
	{
		if (frame == class_EntityArray[i].unitData.position)
			class_ConBuffer.OutputScreen(unitMap, height, width, { 0, 0 }, frame, class_EntityArray[i]);
	}
	class_ConBuffer.OutputScreen(worldMap, unitMap, height, width, { 0, 0 }, frame);
	class_ConBuffer.RenderExtraInfo(playerThreads[currentTurn], turnCounter);

	for (int i = 0; i < numOfUnits; ++i)
	{
		if (class_EntityArray[i].unitData.playerID == currentTurn)
		{
			class_EntityArray[i].unitData.actions = class_EntityArray[i].unitData.maxActions;
		}
	}

	return 1;
}

int WorldClass::UpdateHealthBg(int index)
{
	double hpMod;
	if (class_EntityArray[index].unitData.hp <= 0) //Get rid of the unit by moving it to the bottom right corner
	{
		unitMap[class_EntityArray[index].unitData.position] = worldMap[class_EntityArray[index].unitData.position];
		class_EntityArray[index].unitData.charInfo = worldMap[width*height];
		class_EntityArray[index].unitData.position = width*height;
		unitMap[class_EntityArray[index].unitData.position] = class_EntityArray[index].unitData.charInfo;
		class_EntityArray[index].unitData.maxActions = 0;
		wavPlayer.Load(L"death1.wav");
		wavPlayer.Play();
	}
	else
	{
		hpMod = class_EntityArray[index].unitData.hp / class_EntityArray[index].unitData.maxHP;

		if (hpMod <= 0.25)
			class_EntityArray[index].unitData.charInfo.Attributes = playerColour[class_EntityArray[index].unitData.playerID] | 0x0040;
		else if (hpMod <= 0.5)
			class_EntityArray[index].unitData.charInfo.Attributes = playerColour[class_EntityArray[index].unitData.playerID] | 0x0030;
		else if (hpMod <= 0.75)
			class_EntityArray[index].unitData.charInfo.Attributes = playerColour[class_EntityArray[index].unitData.playerID] | 0x0020;
		else
			class_EntityArray[index].unitData.charInfo.Attributes = playerColour[class_EntityArray[index].unitData.playerID];

		if (class_EntityArray[index].unitData.hp > 0)
			unitMap[class_EntityArray[index].unitData.position] = class_EntityArray[index].unitData.charInfo;
	}


	return 1;
}

int WorldClass::Tick()
{
	keyPress = class_InputClass.GetKeypress();
	CheckInput();
	Render();
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
	//Attack needs to check for map edges
	//Adjusted movement and attack
	//check to see if unit belongs to player before calling the actual move/attack

	//	To attack
	//	UpdateHealthBg(class_EntityClass[SELECTED_UNIT].Attack(DIRECTION))

	if (keyPress.wVirtualKeyCode == VK_UP && keyPress.bKeyDown == true)
	{
		if (moveUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (class_EntityArray[i].unitData.position == frame)
				{
					class_EntityArray[i].MoveUnit('U', &class_EntityArray);
				}
			}
		}
		if (attackUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (class_EntityArray[i].unitData.position == frame)
				{
					this->UpdateHealthBg(class_EntityArray[i].AttackUnit('U', &class_EntityArray));
				}
			}
		}
		frame -= width;
		moveUnit = false;
		attackUnit = false;
	}
	else if (keyPress.wVirtualKeyCode == VK_DOWN && keyPress.bKeyDown == true)
	{
		if (moveUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (class_EntityArray[i].unitData.position == frame)
				{
					class_EntityArray[i].MoveUnit('D', &class_EntityArray);
				}
			}
		}
		if (attackUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (class_EntityArray[i].unitData.position == frame)
				{
					this->UpdateHealthBg(class_EntityArray[i].MoveUnit('D', &class_EntityArray));
				}
			}
		}
		frame += width;
		moveUnit = false;
		attackUnit = false;
	}
	else if (keyPress.wVirtualKeyCode == VK_RIGHT && keyPress.bKeyDown == true)
	{
		if (moveUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (class_EntityArray[i].unitData.position == frame)
				{
					class_EntityArray[i].MoveUnit('R', &class_EntityArray);
				}
			}
		}
		if (attackUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (class_EntityArray[i].unitData.position == frame)
				{
					this->UpdateHealthBg(class_EntityArray[i].AttackUnit('R', &class_EntityArray));
				}
			}
		}
		frame++;
		moveUnit = false;
		attackUnit = false;

	}
	else if (keyPress.wVirtualKeyCode == VK_LEFT && keyPress.bKeyDown == true)
	{
		if (moveUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (class_EntityArray[i].unitData.position == frame)
				{
					class_EntityArray[i].MoveUnit('L', &class_EntityArray);
				}
			}
		}
		if (attackUnit)// i = selected unit j = targeted unit k = distance
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (class_EntityArray[i].unitData.position == frame)
				{
					this->UpdateHealthBg(class_EntityArray[i].AttackUnit('L', &class_EntityArray));
				}
			}
		}
		frame--;
		moveUnit = false;
		attackUnit = false;

	}
	else if (keyPress.wVirtualKeyCode == VK_ESCAPE && keyPress.bKeyDown == true)//Escape
	{
		moveUnit = false;
		attackUnit = false;
	}
	else if (keyPress.wVirtualKeyCode == 0x2D && keyPress.bKeyDown == true) //Insert
	{
		SpawnUnit(7, frame);
	}
	else if (keyPress.wVirtualKeyCode == 0x4D && keyPress.bKeyDown == true) //Movement
	{
		moveUnit = true;
	}
	else if (keyPress.wVirtualKeyCode == 0x41 && keyPress.bKeyDown == true) //Attack
	{
		attackUnit = true;
	}
	else if (keyPress.wVirtualKeyCode == 0x51 && keyPress.bKeyDown == true) //Spawn unitID+1 (Q)
	{
		for (int i = 0; i < numOfUnits; ++i)
		{
			if (frame == class_EntityArray[i].unitData.position && class_EntityArray[i].unitData.playerID == currentTurn)
			{
				if (class_EntityArray[i].unitData.type == 0)
				{
					if (class_UnitInfo.unit[class_EntityArray[i].unitData.unitID + 1].threadCost + playerThreads[currentTurn] >= 0)
					{
						playerThreads[currentTurn] += class_UnitInfo.unit[class_EntityArray[i].unitData.unitID + 1].threadCost;
						SpawnUnit(class_EntityArray[i].unitData.unitID + 1, frame + width);
						class_EntityArray[i].unitData.actions = 0;
					}
				}
				else if (class_EntityArray[i].unitData.type == 1)
				{
					if (class_UnitInfo.unit[class_EntityArray[i].unitData.unitID + 1].threadCost + playerThreads[currentTurn] >= 0)
					{
						playerThreads[currentTurn] += class_UnitInfo.unit[class_EntityArray[i].unitData.unitID + 1].threadCost;
						SpawnUnit(3, frame + width);
						class_EntityArray[i].unitData.actions = 0;
					}
				}
			}
		}
	}
	else if (keyPress.wVirtualKeyCode == 0x57 && keyPress.bKeyDown == true) //Spawn unitID+2 (W)
	{
		for (int i = 0; i < numOfUnits; ++i)
		{
			if (frame == class_EntityArray[i].unitData.position && class_EntityArray[i].unitData.playerID == currentTurn)
			{
				if (class_EntityArray[i].unitData.type == 0)
				{
					if (class_UnitInfo.unit[class_EntityArray[i].unitData.unitID + 2].threadCost + playerThreads[currentTurn] >= 0)//Convert to unitinfo[unitID+2]
					{
						playerThreads[currentTurn] += class_UnitInfo.unit[class_EntityArray[i].unitData.unitID + 2].threadCost;
						SpawnUnit(class_EntityArray[i].unitData.unitID + 2, frame + width);
						class_EntityArray[i].unitData.actions = 0;
					}
				}
				else if (class_EntityArray[i].unitData.type == 1)
				{
					if (class_UnitInfo.unit[class_EntityArray[i].unitData.unitID + 2].threadCost + playerThreads[currentTurn] >= 0)
					{
						playerThreads[currentTurn] = playerThreads[currentTurn] + class_UnitInfo.unit[class_EntityArray[i].unitData.unitID + 2].threadCost;
						SpawnUnit(4, frame + width);
						class_EntityArray[i].unitData.actions = 0;
					}
				}
			}
		}
	}
	return 1;
}

//Just a sumary of controls

//Insert: Spawn OP testing unit

//A then Arrow key: Attack in direction

//M then Arrow key: Move in direction

//Esc: Cancel move/attack to free cursor

//Q:
//	if base:	spawns worker
//	if worker:	spawns resource building

//W:
//	if base:	spawns general melee unit
//	if worker:	spawns general upgrade building