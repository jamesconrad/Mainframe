#ifndef ABILITYINFO_H
#define ABILITYINFO_H

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