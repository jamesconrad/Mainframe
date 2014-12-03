#include <Windows.h>
#include <vector>
#include "entityclass.h"

EntityClass::EntityClass()
{
}

EntityClass::~EntityClass()
{
}

int EntityClass::SetUnitData(UnitData unitData)
{
	EntityClass::unitData = unitData;
	return 1;
}

int EntityClass::Initialize(int worldWidth, int worldHeight, CHAR_INFO *worldMap, CHAR_INFO *unitMap)
{
	this->worldWidth = worldWidth;
	this->worldHeight = worldHeight;
	this->worldMap = worldMap;
	this->unitMap = unitMap;
	return 1;
}

int EntityClass::MoveUnit(char dir, std::vector<EntityClass> *entityArray)
{
	bool collision = false;
	//check to see if space is occupied then move if possible
	if (dir == 'U')
	{
		if (unitData.position - worldWidth >= 0)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == unitData.position - worldWidth)
				{
					collision = true;
				}
			}
			if (unitData.position - worldWidth >= 0 && !collision && unitData.actions > 0)
			{
				unitMap[unitData.position] = worldMap[unitData.position];
				unitData.position -= worldWidth;
				unitMap[unitData.position] = unitData.charInfo;
				unitData.actions--;
			}
		}
	}
	else if (dir == 'D')
	{
		if (unitData.position + worldWidth < worldHeight * worldWidth)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == unitData.position + worldWidth)
				{
					collision = true;
				}
			}
			if (unitData.position + worldWidth < worldWidth*worldHeight && !collision && unitData.actions > 0)
			{
				unitMap[unitData.position] = worldMap[unitData.position];

				unitData.position += worldWidth;

				unitMap[unitData.position] = unitData.charInfo;

				unitData.actions--;
			}
		}
	}
	else if (dir == 'L')
	{
		if (unitData.position % worldWidth != 0)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == unitData.position - 1)
				{
					collision = true;
				}
			}
			if (unitData.position % worldWidth != 0 && !collision && unitData.actions > 0)
			{
				unitMap[unitData.position] = worldMap[unitData.position];
				unitData.position -= 1;
				unitMap[unitData.position] = unitData.charInfo;
				unitData.actions--;
			}
		}
	}
	else if (dir == 'R')
	{
		if (unitData.position % worldWidth != worldWidth - 1)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == unitData.position + 1)
				{
					collision = true;
				}
			}
			if (unitData.position % worldWidth != worldWidth - 1 && !collision && unitData.actions > 0)
			{
				unitMap[unitData.position] = worldMap[unitData.position];
				unitData.position += 1;
				unitMap[unitData.position] = unitData.charInfo;
				unitData.actions--;
			}
		}
	}

	return 1;
}

int EntityClass::AttackUnit(char dir, std::vector<EntityClass> *entityArray, int me)
{
	if (dir == 'U')
	{
		for (int k = 1; k <= unitData.range; k++)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				//Find a target
				if (entityArray->at(j).unitData.position == (unitData.position - (k * 48)) && entityArray->at(j).unitData.playerID != unitData.playerID && unitData.actions > 0)
				{
					//Check if we have more attack then them
					if (unitData.attack - entityArray->at(j).unitData.defense > 0)
					{
						//Deal full damage
						entityArray->at(j).unitData.hp -= (unitData.attack - entityArray->at(j).unitData.defense);
						unitData.actions = 0;
						return j;
					}
					else if (unitData.attack - entityArray->at(j).unitData.defense <= 0)
					{
						//Deal one damage
						entityArray->at(j).unitData.hp--;
						unitData.actions = 0;
						return j;
					}
					else {}
					//no damage done
				}
			}
		}
	}
	else if (dir == 'L')
	{
		for (int k = 1; k <= unitData.range; k++)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == (unitData.position - k) && entityArray->at(j).unitData.playerID != unitData.playerID && unitData.actions > 0)
				{
					if (unitData.attack - entityArray->at(j).unitData.defense > 0)
					{
						entityArray->at(j).unitData.hp -= (unitData.attack - entityArray->at(j).unitData.defense);
						unitData.actions = 0;
						return j;
					}
					else if (unitData.attack - entityArray->at(j).unitData.defense <= 0)
					{
						entityArray->at(j).unitData.hp--;
						unitData.actions = 0;
						return j;
					}
					else {}
					//no damage done
				}
			}
		}
	}
	else if (dir == 'R')
	{
		for (int k = 1; k <= unitData.range; k++)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == unitData.position + k && entityArray->at(j).unitData.playerID != unitData.playerID && unitData.actions > 0)
				{
					if (unitData.attack - entityArray->at(j).unitData.defense > 0)
					{
						entityArray->at(j).unitData.hp -= (unitData.attack - entityArray->at(j).unitData.defense);
						unitData.actions = 0;
						return j;
					}
					else if (unitData.attack - entityArray->at(j).unitData.defense <= 0)
					{
						entityArray->at(j).unitData.hp--;
						unitData.actions = 0;
						return j;
					}
					else {}
					//no damage done
				}
			}
		}
	}
	else if (dir == 'D')
	{
		for (int k = 1; k <= unitData.range; k++)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == (unitData.position + (48 * k)) && entityArray->at(j).unitData.playerID != unitData.playerID && unitData.actions > 0)
				{
					if (unitData.attack - entityArray->at(j).unitData.defense > 0)
					{
						entityArray->at(j).unitData.hp -= (unitData.attack - entityArray->at(j).unitData.defense);
						unitData.actions = 0;
						return j;
					}
					else if (unitData.attack - entityArray->at(j).unitData.defense <= 0)
					{
						entityArray->at(j).unitData.hp--;
						unitData.actions = 0;
						return j;
					}
					else {}
					//no damage done
				}
			}
		}
	}
	return 0;
}

int EntityClass::UseAbility(int num, EntityClass *entity)
{
	if (num == 1)
	{

	}

	return 1;
}