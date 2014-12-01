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
int WorldClass::Initialize(CHAR_INFO* generation, int frame, int width, int height, int numOfPlayers, int numOfUnits, int numOfAi)
{
	worldMap = generation;

	isInGame = true;
	moveUnit = false;
	attackUnit = false;
	frameChanged = true;

	_conBuffer.Initialize();

	unitMap = (CHAR_INFO*)malloc(sizeof(CHAR_INFO*)*width*height);

	memcpy(unitMap, worldMap, sizeof(CHAR_INFO)*width*height);
	this->height = height;
	this->width = width;
	this->numOfUnits = numOfUnits;

	_unitInfo.Initialize();
	_inputClass.Initialize();

	_audioClass.Load(L"Music/DST-3rdBallad.mp3");
	_audioClass.Play();

	playerColour[0] = 0x0001 | 0x0008;
	playerColour[1] = 0x0002 | 0x0008;
	playerColour[2] = 0x0003 | 0x0008;
	playerColour[3] = 0x0004 | 0x0008;
	playerColour[4] = 0x0005 | 0x0008;
	playerColour[5] = 0x0006 | 0x0008;

	currentTurn = 0;
	this->numOfPlayers = numOfPlayers;

	playerThreads = (int*)malloc(sizeof(int)*numOfPlayers);
	alivePlayers = (int*)malloc(sizeof(int)*numOfPlayers);

	prevKeyPress = _inputClass.GetKeypress();
	keyPress = _inputClass.GetKeypress();

	for (int i = 0; i < numOfPlayers; ++i)
	{
		playerThreads[i] = 3;
		alivePlayers[i] = true;
	}

	int rng, done = -1;
	bool validDist = true;
	int dist = sqrt(pow(width, 2) + pow(height, 2)), tmpDist;
	for (int i = 0; i < numOfPlayers; ++i)
	{
		do
			rng = rand() % (width*height);
		while (unitMap[rng].Attributes == 0x0001);

		SpawnUnit(0, rng % (width*height));
		++currentTurn;
	}
	this->frame = _entityArray[1].unitData.position;

	currentTurn = 0;
	_conBuffer.UpdateBorderColour(currentTurn);
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

	//UpdateUnitMap();

	frameCoords.X++;
	frameCoords.Y++;
	//if (frameChanged)
	//{
	//	SetConsoleCursorPosition(_conBuffer.hConsole, frameCoords);
	//	frameChanged = false;
	//}
	bool unitTargeted = false;
	for (int i = 0; i < numOfUnits; ++i)
	{
		if (frame == _entityArray[i].unitData.position)
		{
			unitTargeted = true;
			_conBuffer.OutputScreen(unitMap, height, width, { 0, 0 }, frame, _entityArray[i]);
		}

	}
	if (!unitTargeted)
		_conBuffer.OutputScreen(worldMap, unitMap, height, width, { 0, 0 }, frame);
	_conBuffer.RenderExtraInfo(playerThreads[currentTurn], turnCounter);

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
	UnitData unitData = _unitInfo.unit[id];


	unitData.playerID = currentTurn;
	unitData.position = index;

	EntityClass tempEntity;

	tempEntity.unitData = unitData;
	tempEntity.unitData.charInfo.Attributes = playerColour[currentTurn];

	_entityArray.push_back(tempEntity);
	_entityArray[numOfUnits].Initialize(width, height, worldMap, unitMap);
	_entityArray[numOfUnits].unitData = tempEntity.unitData;
	unitMap[unitData.position] = tempEntity.unitData.charInfo;

	//Set actions to 0 for this turn only
	_entityArray[numOfUnits].unitData.actions = 0;


	numOfUnits++;
	return numOfUnits;
}

int WorldClass::UpdateUnitMap()
{
	for (int i = 0; i < numOfUnits; i++)
		unitMap[_entityArray[i].unitData.position] = _entityArray[i].unitData.charInfo;

	return 1;
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

	for (int i = 0; i < numOfUnits; i++)
	{
		if (_entityArray[i].unitData.playerID == currentTurn)
		{
			playerThreads[currentTurn] += _entityArray[i].unitData.resourcesPerTurn;
		}
	}


	_conBuffer.UpdateBorderColour(currentTurn);

	for (int i = 0; i < numOfUnits; ++i)
	{
		if (frame == _entityArray[i].unitData.position)
			_conBuffer.OutputScreen(unitMap, height, width, { 0, 0 }, frame, _entityArray[i]);
	}
	_conBuffer.OutputScreen(worldMap, unitMap, height, width, { 0, 0 }, frame);
	_conBuffer.RenderExtraInfo(playerThreads[currentTurn], turnCounter);

	for (int i = 0; i < numOfUnits; ++i)
	{
		if (_entityArray[i].unitData.playerID == currentTurn)
		{
			_entityArray[i].unitData.actions = _entityArray[i].unitData.maxActions;
		}
	}

	return 1;
}

int WorldClass::UpdateHealthBg(int index)
{
	double hpMod;
	if (_entityArray[index].unitData.hp <= 0) //Get rid of the unit by moving it to the bottom right corner
	{
		unitMap[_entityArray[index].unitData.position] = worldMap[_entityArray[index].unitData.position];
		_entityArray[index].unitData.charInfo = worldMap[width*height];
		_entityArray[index].unitData.position = width*height;
		unitMap[_entityArray[index].unitData.position] = _entityArray[index].unitData.charInfo;
		_entityArray[index].unitData.maxActions = 0;
		wavPlayer.Load(L"Music/death1.wav");
		wavPlayer.Play();
	}
	else
	{
		hpMod = _entityArray[index].unitData.hp / _entityArray[index].unitData.maxHP;

		if (hpMod <= 0.25)
			_entityArray[index].unitData.charInfo.Attributes = playerColour[_entityArray[index].unitData.playerID] | 0x0040;
		else if (hpMod <= 0.5)
			_entityArray[index].unitData.charInfo.Attributes = playerColour[_entityArray[index].unitData.playerID] | 0x0030;
		else if (hpMod <= 0.75)
			_entityArray[index].unitData.charInfo.Attributes = playerColour[_entityArray[index].unitData.playerID] | 0x0020;
		else
			_entityArray[index].unitData.charInfo.Attributes = playerColour[_entityArray[index].unitData.playerID];

		if (_entityArray[index].unitData.hp > 0)
			unitMap[_entityArray[index].unitData.position] = _entityArray[index].unitData.charInfo;
	}


	return 1;
}

int WorldClass::Tick()
{
	Update(CheckInput());
	Render();
	return 1;
}

int WorldClass::Update(int index)
{
	//Check to see if they can make a move
	bool outOfMoves = true;
	for (int i = 0; i < numOfUnits; i++)
	{
		if (_entityArray[i].unitData.playerID == currentTurn)
		{
			if (_entityArray[i].unitData.actions != 0 && _entityArray[i].unitData.hp != 0)
				outOfMoves = false;
		}
	}

	//Check to see if alive
	for (int i = 0; i < numOfUnits; i++)
	{
		if (_entityArray[i].unitData.unitID == 0 && _entityArray[i].unitData.hp <= 0)
			alivePlayers[_entityArray[i].unitData.playerID] = false;
	}

	//Game over if only alive
	bool lastStanding = true;
	for (int i = 0; i < numOfPlayers; i++)
	{
		if (alivePlayers[i] = true && i != currentTurn)
			lastStanding = false;
	}
	//Exit game if only person left
	if (lastStanding)
	{
		isInGame = false;
		winner = currentTurn;
	}

	//Next turn if dead or out of moves
	if (outOfMoves || alivePlayers[currentTurn])
		NextTurn();



	UpdateUnitMap();
	UpdateHealthBg(index);

	return 1;
}

bool WorldClass::InGame()
{
	return isInGame;
}

int WorldClass::CheckInput()
{
	keyPress = _inputClass.GetKeypress();
	bool collision = false;
	int returnVal = 0;
	if (keyPress.wVirtualKeyCode == VK_SPACE && keyPress.bKeyDown == true)
	{
		WorldClass::NextTurn();
		//Sleep(1000);
	}
	//Attack needs to check for map edges
	//Adjusted movement and attack
	//check to see if unit belongs to player before calling the actual move/attack

	//	To attack
	//	UpdateHealthBg(_entityClass[SELECTED_UNIT].Attack(DIRECTION))

	if (keyPress.wVirtualKeyCode == VK_UP && keyPress.bKeyDown == true)
	{
		if (moveUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (_entityArray[i].unitData.position == frame)
				{
					moveUnit = false;
					_entityArray[i].MoveUnit('U', &_entityArray);
				}
			}
		}
		if (attackUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (_entityArray[i].unitData.position == frame)
				{
					attackUnit = false;
					//this->UpdateHealthBg(_entityArray[i].AttackUnit('U', &_entityArray));
					return _entityArray[i].AttackUnit('U', &_entityArray);
				}
			}
		}
		frame -= width;
	}
	else if (keyPress.wVirtualKeyCode == VK_DOWN && keyPress.bKeyDown == true)
	{
		if (moveUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (_entityArray[i].unitData.position == frame)
				{
					moveUnit = false;
					_entityArray[i].MoveUnit('D', &_entityArray);
				}
			}
		}
		if (attackUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (_entityArray[i].unitData.position == frame)
				{
					attackUnit = false;
					//this->UpdateHealthBg(_entityArray[i].MoveUnit('D', &_entityArray));
					return _entityArray[i].AttackUnit('D', &_entityArray);
				}
			}
		}
		frame += width;
	}
	else if (keyPress.wVirtualKeyCode == VK_RIGHT && keyPress.bKeyDown == true)
	{
		if (moveUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (_entityArray[i].unitData.position == frame)
				{
					moveUnit = false;
					_entityArray[i].MoveUnit('R', &_entityArray);
				}
			}
		}
		if (attackUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (_entityArray[i].unitData.position == frame)
				{
					attackUnit = false;
					//this->UpdateHealthBg(_entityArray[i].AttackUnit('R', &_entityArray));
					return _entityArray[i].AttackUnit('R', &_entityArray);
				}
			}
		}
		frame++;

	}
	else if (keyPress.wVirtualKeyCode == VK_LEFT && keyPress.bKeyDown == true)
	{
		if (moveUnit)
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (_entityArray[i].unitData.position == frame)
				{
					moveUnit = false;
					_entityArray[i].MoveUnit('L', &_entityArray);
				}
			}
		}
		if (attackUnit)// i = selected unit j = targeted unit k = distance
		{
			for (int i = 0; i < numOfUnits; i++)
			{
				if (_entityArray[i].unitData.position == frame)
				{
					attackUnit = false;
					//this->UpdateHealthBg(_entityArray[i].AttackUnit('L', &_entityArray));
					return _entityArray[i].AttackUnit('L', &_entityArray);
				}
			}
		}
		frame--;

	}
	else if (keyPress.wVirtualKeyCode == VK_ESCAPE && keyPress.bKeyDown == true)//Escape
	{
		moveUnit = false;
		attackUnit = false;
		Save();
		exit(0);
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
			if (frame == _entityArray[i].unitData.position && _entityArray[i].unitData.playerID == currentTurn)
			{
				if (_entityArray[i].unitData.type == 0)
				{
					if (_unitInfo.unit[_entityArray[i].unitData.unitID + 1].threadCost + playerThreads[currentTurn] >= 0)
					{
						playerThreads[currentTurn] += _unitInfo.unit[_entityArray[i].unitData.unitID + 1].threadCost;
						SpawnUnit(_entityArray[i].unitData.unitID + 1, frame + width);
						_entityArray[i].unitData.actions = 0;
					}
				}
				else if (_entityArray[i].unitData.type == 1)
				{
					if (_unitInfo.unit[_entityArray[i].unitData.unitID + 1].threadCost + playerThreads[currentTurn] >= 0)
					{
						playerThreads[currentTurn] += _unitInfo.unit[_entityArray[i].unitData.unitID + 1].threadCost;
						SpawnUnit(3, frame + width);
						_entityArray[i].unitData.actions = 0;
					}
				}
			}
		}
	}
	else if (keyPress.wVirtualKeyCode == 0x57 && keyPress.bKeyDown == true) //Spawn unitID+2 (W)
	{
		for (int i = 0; i < numOfUnits; ++i)
		{
			if (frame == _entityArray[i].unitData.position && _entityArray[i].unitData.playerID == currentTurn)
			{
				if (_entityArray[i].unitData.type == 0)
				{
					if (_unitInfo.unit[_entityArray[i].unitData.unitID + 2].threadCost + playerThreads[currentTurn] >= 0)//Convert to unitinfo[unitID+2]
					{
						playerThreads[currentTurn] += _unitInfo.unit[_entityArray[i].unitData.unitID + 2].threadCost;
						SpawnUnit(_entityArray[i].unitData.unitID + 2, frame + width);
						_entityArray[i].unitData.actions = 0;
					}
				}
				else if (_entityArray[i].unitData.type == 1)
				{
					if (_unitInfo.unit[_entityArray[i].unitData.unitID + 2].threadCost + playerThreads[currentTurn] >= 0)
					{
						playerThreads[currentTurn] = playerThreads[currentTurn] + _unitInfo.unit[_entityArray[i].unitData.unitID + 2].threadCost;
						SpawnUnit(4, frame + width);
						_entityArray[i].unitData.actions = 0;
					}
				}
			}
		}
	}
	return 1;
}

int WorldClass::Save()
{
	FILE *saveFile;
	saveFile = fopen("Save/map", "wb");
	fwrite(worldMap, sizeof(CHAR_INFO), width*height, saveFile);

	//Blank the file
	saveFile = fopen("Save/units", "wb");
	//Actually do the writing
	saveFile = fopen("Save/units", "ab");
	for (int i = 0; i < numOfUnits; i++)
		fwrite(&_entityArray[i], sizeof(EntityClass), 1, saveFile);
	
	saveFile = fopen("Save/misc", "w");
	fwrite(&numOfPlayers, sizeof(int), 1, saveFile);
	saveFile = fopen("Save/misc", "a");
	fwrite(&numOfUnits, sizeof(int), 1, saveFile);
	fwrite(&width, sizeof(int), 1, saveFile);
	fwrite(&height, sizeof(int), 1, saveFile);
	fwrite(&turnCounter, sizeof(int), 1, saveFile);
	fwrite(&currentTurn, sizeof(int), 1, saveFile);
	for (int i = 0; i < numOfPlayers; i++)
		fwrite(&playerThreads[i], sizeof(int), 1, saveFile);

	return 1;
}

int WorldClass::Load()
{
	FILE *saveFile;
	saveFile = fopen("Save/misc", "r");
	fread(&numOfPlayers, sizeof(int), 1, saveFile);
	fread(&numOfUnits, sizeof(int), 1, saveFile);
	fread(&width, sizeof(int), 1, saveFile);
	fread(&height, sizeof(int), 1, saveFile);
	fread(&turnCounter, sizeof(int), 1, saveFile);
	fread(&currentTurn, sizeof(int), 1, saveFile);
	playerThreads = (int*)malloc(sizeof(int)*numOfPlayers);
	for (int i = 0; i < numOfPlayers; i++)
		fread(&playerThreads[i], sizeof(int), 1, saveFile);


	saveFile = fopen("Save/map", "rb");
	CHAR_INFO* tmpMap = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*width*height);
	fread(tmpMap, sizeof(CHAR_INFO), width*height, saveFile);

	saveFile = fopen("Save/units", "rb");
	EntityClass* tmpEntArr = (EntityClass*)malloc(sizeof(EntityClass)*numOfUnits);
	for (int i = 0; i < numOfUnits; i++)
		fread(&tmpEntArr[i], sizeof(EntityClass), 1, saveFile);
	for (int i = 0; i < numOfUnits; i++)
		_entityArray.push_back(tmpEntArr[i]);
	free(tmpEntArr);

	//Initialize(tmpMap, 1, width, height, numOfPlayers, numOfUnits);

	//Reuse portions of Initialize();

	worldMap = tmpMap;

	isInGame = true;
	moveUnit = false;
	attackUnit = false;
	frameChanged = true;

	_conBuffer.Initialize();

	unitMap = (CHAR_INFO*)malloc(sizeof(CHAR_INFO*)*width*height);

	memcpy(unitMap, worldMap, sizeof(CHAR_INFO)*width*height);
	frame = 0;

	_unitInfo.Initialize();
	_inputClass.Initialize();

	_audioClass.Load(L"Music/DST-3rdBallad.mp3");
	_audioClass.Play();

	playerColour[0] = 0x0001 | 0x0008;
	playerColour[1] = 0x0002 | 0x0008;
	playerColour[2] = 0x0003 | 0x0008;
	playerColour[3] = 0x0004 | 0x0008;
	playerColour[4] = 0x0005 | 0x0008;
	playerColour[5] = 0x0006 | 0x0008;

	alivePlayers = (int*)malloc(sizeof(int)*numOfPlayers);

	prevKeyPress = _inputClass.GetKeypress();
	keyPress = _inputClass.GetKeypress();

	for (int i = 0; i < numOfPlayers; ++i)
	{
		alivePlayers[i] = true;
	}

	_conBuffer.UpdateBorderColour(currentTurn);

	return 1;
}

int WorldClass::GetWinner()
{
	return winner;
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