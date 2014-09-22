#ifndef UNITDATA_H
#define UNITDATA_H

#include <Windows.h>

namespace
{
	struct UnitData
	{
		CHAR_INFO charInfo;
		int playerID, //player number to determine unit colour and hostility
			maxHP, //determins max health of unit and sets background accordingly
			hp,  //determines health of unit and sets background accordingly
			unitID,
			actions, //dependant on unit one moved for every attempt made, attacking sets to 0
			attack, //damage dealt on attack
			defense, //defenise - attack = damage dealt
			range, // range of attack, hits first unit in way
			type, //0 = building, 1 = land, 2 = air, 3 = water
			position; //index number of unit
	};
}

class UnitInfoClass {
public:	
	UnitData unit[8];

	UnitInfoClass();
	UnitInfoClass(const UnitInfoClass&);
	~UnitInfoClass();
	int Initialize();
};

#endif