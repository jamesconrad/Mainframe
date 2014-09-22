#ifndef ENTITYCLASS_H
#define ENTITYCLASS_H

#include <Windows.h>
#include "unitinfoclass.h"

class EntityClass
{
public:
	UnitData unitData;

	EntityClass();
	EntityClass(const EntityClass&);
	~EntityClass();
	int Initialize(UnitData unitData);

	int MoveUnit(char direction);
	int AttackUnit(UnitData src, char direction);

	int SetUnitData(UnitData unitData);
};

#endif