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
	//UnitInfo::unit[unitID] = { unitCharacter , 0 , maxHP , HP, unitID , actions , maxActions , attack , defense , range , type , 0, true }
	unit[0] = { BASE_CHAR_INFO, 0, 10, 10, 0, 1, 1, 10, 100, 3, 0, 0 }; //Start base
	unit[0].charInfo.Char.UnicodeChar = 233;
	unit[0].charInfo.Attributes = 0x0007;
	unit[1] = { BASE_CHAR_INFO, 0, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0 }; //Worker
	unit[2] = { BASE_CHAR_INFO, 0, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0 }; //Basic Land unit

	unit[7] = { BASE_CHAR_INFO, 0, 1, 1, 7, 100, 100, 1000, 1000, 100, 1, 0 }; //Unit for Land testing
	unit[7].charInfo.Char.UnicodeChar = 8734;
	unit[7].charInfo.Attributes = 0x0007;
	return 1;
}