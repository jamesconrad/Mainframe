#ifndef ABILITYINFO_H
#define ABILITYINFO_H
//AbilityInfo:
//much like UnitIfo
//TODO:
//Make an interpreter to use abilities.
#include <Windows.h>

namespace
{
	struct AbiltiyInfo
	{
		int id;
		bool affectsAll;
		int affects,
			maxHpMod,
			hpMod,
			dmgMod,
			defMod,
			maxActionsMod,
			actionsMod,
			rangeMod,
			castTurns,
			castMod,
			duration,
			unitSpawnId;
	};
}

class AbiltiyInfoClass
{
public:
	AbiltiyInfo ability[8];

	AbiltiyInfoClass();
	AbiltiyInfoClass(const AbiltiyInfoClass&);
	~AbiltiyInfoClass();
	int Initialize();
};

#endif