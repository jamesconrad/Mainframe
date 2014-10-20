#include <Windows.h>
#include <vector>
#include "entityclass.h"

EntityClass::EntityClass()
{
}

//EntityClass::EntityClass(const EntityClass&)
//{
//}

EntityClass::~EntityClass()
{
}

int EntityClass::SetUnitData(UnitData unitData)
{
	EntityClass::unitData = unitData;
	return 1;
}


int EntityClass::Initialize(UnitData unitData, int worldWidth, int worldHeight, CHAR_INFO *worldMap, CHAR_INFO *unitMap)
{
	EntityClass::unitData = unitData;
	this->worldWidth = worldWidth;
	this->worldHeight = worldHeight;
	this->worldMap = worldMap;
	this->unitMap = unitMap;
	return 1;
}

int EntityClass::MoveUnit(char dir, std::vector<EntityClass> *entityArray)
{
	bool collision = false;
	//check to see if space is occupied
	if (dir == 'U')
	{
		if (this->unitData.position - worldWidth >= 0)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == this->unitData.position - worldWidth)
				{
					collision = true;
				}
			}
			if (this->unitData.position - worldWidth >= 0 && !collision && this->unitData.actions > 0)
			{
				unitMap[this->unitData.position] = worldMap[this->unitData.position];
				this->unitData.position -= worldWidth;
				unitMap[this->unitData.position] = this->unitData.charInfo;
				this->unitData.actions--;
			}
		}
	}
	else if (dir == 'D')
	{
		if (this->unitData.position + worldWidth < worldHeight * worldWidth)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == this->unitData.position + worldWidth)
				{
					collision = true;
				}
			}
			if (this->unitData.position + worldWidth < worldWidth*worldHeight && !collision && this->unitData.actions > 0)
			{
				unitMap[this->unitData.position] = worldMap[this->unitData.position];
				this->unitData.position += worldWidth;
				unitMap[this->unitData.position] = this->unitData.charInfo;
				this->unitData.actions--;
			}
		}
	}
	else if (dir == 'L')
	{
		if (this->unitData.position % worldWidth != 0)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == this->unitData.position - 1)
				{
					collision = true;
				}
			}
			if (this->unitData.position % worldWidth != 0 && !collision && this->unitData.actions > 0)
			{
				unitMap[this->unitData.position] = worldMap[this->unitData.position];
				this->unitData.position -= 1;
				unitMap[this->unitData.position] = this->unitData.charInfo;
				this->unitData.actions--;
			}
		}
	}
	else if (dir == 'R')
	{
		if (this->unitData.position % worldWidth != worldWidth - 1)
		{
			for (int j = 0; j < entityArray->size(); j++)
			{
				if (entityArray->at(j).unitData.position == this->unitData.position + 1)
				{
					collision = true;
				}
			}
			if (this->unitData.position % worldWidth != worldWidth - 1 && !collision && this->unitData.actions > 0)
			{
				unitMap[this->unitData.position] = worldMap[this->unitData.position];
				this->unitData.position += 1;
				unitMap[this->unitData.position] = this->unitData.charInfo;
				this->unitData.actions--;
			}
		}
	}

	return 1;
}

int EntityClass::AttackUnit(char dir, std::vector<EntityClass> *entityArray)
{
	if (dir == 'U')
	{
		for (int j = 0; j < entityArray->size(); j++)
		{
			for (int k = 1; k <= this->unitData.range; ++k)
			{
				if (entityArray->at(j).unitData.position == this->unitData.position - k && entityArray->at(j).unitData.playerID != this->unitData.playerID && this->unitData.actions > 0)
				{
					if (this->unitData.attack - entityArray->at(j).unitData.defense > 0)
					{
						entityArray->at(j).unitData.hp -= (this->unitData.attack - entityArray->at(j).unitData.defense);
						this->unitData.actions = 0;
						return j;
					}
					else if (this->unitData.attack - entityArray->at(j).unitData.defense == 0)
					{
						entityArray->at(j).unitData.hp--;
						this->unitData.actions = 0;
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
		for (int j = 0; j < entityArray->size(); j++)
		{
			for (int k = 1; k <= this->unitData.range; ++k)
			{
				if (entityArray->at(j).unitData.position == this->unitData.position + 8 * k && entityArray->at(j).unitData.playerID != this->unitData.playerID && this->unitData.actions > 0)
				{
					if (this->unitData.attack - entityArray->at(j).unitData.defense > 0)
					{
						entityArray->at(j).unitData.hp -= (this->unitData.attack - entityArray->at(j).unitData.defense);
						this->unitData.actions = 0;
						return j;
					}
					else if (this->unitData.attack - entityArray->at(j).unitData.defense == 0)
					{
						entityArray->at(j).unitData.hp--;
						this->unitData.actions = 0;
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
		for (int j = 0; j < entityArray->size(); j++)
		{
			for (int k = 1; k <= this->unitData.range; k++)
			{
				if (entityArray->at(j).unitData.position == (this->unitData.position - k) && entityArray->at(j).unitData.playerID != this->unitData.playerID && this->unitData.actions > 0)
				{
					if (this->unitData.attack - entityArray->at(j).unitData.defense > 0)
					{
						entityArray->at(j).unitData.hp -= (this->unitData.attack - entityArray->at(j).unitData.defense);
						this->unitData.actions = 0;
						return j;
					}
					else if (this->unitData.attack - entityArray->at(j).unitData.defense == 0)
					{
						entityArray->at(j).unitData.hp--;
						this->unitData.actions = 0;
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
		for (int j = 0; j < entityArray->size(); j++)
		{
			for (int k = 1; k <= this->unitData.range; ++k)
			{
				if (entityArray->at(j).unitData.position == this->unitData.position + k && entityArray->at(j).unitData.playerID != this->unitData.playerID && this->unitData.actions > 0)
				{
					if (this->unitData.attack - entityArray->at(j).unitData.defense > 0)
					{
						entityArray->at(j).unitData.hp -= (this->unitData.attack - entityArray->at(j).unitData.defense);
						this->unitData.actions = 0;
						return j;
					}
					else if (this->unitData.attack - entityArray->at(j).unitData.defense == 0)
					{
						entityArray->at(j).unitData.hp--;
						this->unitData.actions = 0;
						return j;
					}
					else {}
					//no damage done
				}
			}
		}
	}
	return 1;
}