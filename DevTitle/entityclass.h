#ifndef ENTITYCLASS_H
#define ENTITYCLASS_H

#include <vector>
#include "unitinfoclass.h"

class EntityClass
{
private:
	int worldWidth, worldHeight, playerColour[6];
	CHAR_INFO *worldMap, *unitMap;



	int UpdateHealthBg(CHAR_INFO* unitMap, CHAR_INFO* worldMap);
public:
	UnitData unitData;

	EntityClass();
	/*EntityClass(const EntityClass&);*/
	~EntityClass();
	int Initialize(/*UnitData unitData,*/ int worldWidth, int worldHeight, CHAR_INFO *worldMap, CHAR_INFO *unitMap);

	int MoveUnit(char direction, std::vector<EntityClass> *entityArray);
	int AttackUnit(char direction, std::vector<EntityClass> *entityArray);
	int UseAbility(int num, EntityClass *entity);

	int SetUnitData(UnitData unitData);
};

#endif