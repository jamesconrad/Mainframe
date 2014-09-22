#include "unitinfoclass.h"

UnitInfoClass::UnitInfoClass()
{
}

UnitInfoClass::UnitInfoClass(const UnitInfoClass&)
{
}

UnitInfoClass::~UnitInfoClass()
{
}

int UnitInfoClass::Initialize()
{
	CHAR_INFO BASE_CHAR_INFO;
	BASE_CHAR_INFO.Char.UnicodeChar = 1;
	BASE_CHAR_INFO.Attributes = 0x007;

	//To add another unit
	//UnitInfo::unit[unitID] = { unitCharacter , 0 , maxHP , HP, unitID , actions , attack , defense , range , type , 0, true }
	UnitInfoClass::unit[0] = { BASE_CHAR_INFO, 0, 10, 10, 0, 1, 10, 100, 3, 0, 0 }; //Start base
	UnitInfoClass::unit[0].charInfo.Char.UnicodeChar = 233;
	UnitInfoClass::unit[0].charInfo.Attributes = 0x0007;
	UnitInfoClass::unit[1] = { BASE_CHAR_INFO, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0 }; //Worker
	UnitInfoClass::unit[2] = { BASE_CHAR_INFO, 0, 2, 2, 2, 2, 2, 1, 1, 0, 0 }; //Basic Land unit

	UnitInfoClass::unit[7] = { BASE_CHAR_INFO, 0, 1, 1, 7, 100, 1000, 1000, 100, 1, 0 }; //Unit for Land testing
	UnitInfoClass::unit[7].charInfo.Char.UnicodeChar = 8734;
	UnitInfoClass::unit[7].charInfo.Attributes = 0x0007;
	return 1;
}