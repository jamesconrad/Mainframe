#include "abilityinfoclass.h"

AbiltiyInfoClass::AbiltiyInfoClass()
{
}

AbiltiyInfoClass::AbiltiyInfoClass(const AbiltiyInfoClass&)
{
}

AbiltiyInfoClass::~AbiltiyInfoClass()
{
}

int AbiltiyInfoClass::Initialize()
{
	// ability[id] = {id, affectsAll, affects/target, maxHpMod,	hpMod, dmgMod, defMod, maxActionsMod, actionsMod, rangeMod, castTurns, castMod, duration, unitSpawnId;
	ability[0] = { 0, false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };//spawn worker
	ability[1] = { 1, false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 };//spawn basic fighter
	ability[2] = { 2, false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 };//spawn general resource building
	ability[3] = { 3, false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 };//spawn upgrade building
	ability[4] = { 4, true, 0, 0, 0, 1, 1, 0, 0, 0, 5, 0, 9999, -1 };//basic upgrade +1 dmg, +1 def, 5 turn cast time
	ability[5] = { 5, false, 0, 0, 1, 0, 0, 0, -1, 0, 1, 0, 1, -1 };//basic heal

	return 1;
}