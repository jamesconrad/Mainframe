#include <Windows.h>
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


int EntityClass::Initialize(UnitData unitData)
{
	EntityClass::unitData = unitData;
	return 1;
}

int MoveUnit(char direction)
{
	//check to see if space is occupied

	return 1;
}

int AttackUnit(UnitData srcUnit, char direction)
{
	if (srcUnit.actions = 0)
	{
		return 0;
	}
	for (int i = 0; i < srcUnit.range; i++)
	{

	}
	srcUnit.actions = 0;
	return 1;
}