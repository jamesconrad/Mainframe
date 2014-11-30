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
	//Buildings will spawn the 2 units after them

	//UnitInfo::unit[unitID] = { unitCharacter , 0 , maxHP , HP, unitID , actions , maxActions , attack , defense , range , type , 0 , threadCost, ability1, ability2, ability3, resourcesPerTurn, "name"}	
	unit[0] = { BASE_CHAR_INFO, 0, 10, 10, 0, 1, 1, 10, 100, 0, 0, 0, 0, 2, 0, 0, 2, { 'M','a','i','n','f','r','a','m','e' } }; //Start base
	unit[0].charInfo.Char.UnicodeChar = 920;
	unit[0].charInfo.Attributes = 0x0007;
	unit[1] = { BASE_CHAR_INFO, 0, 1, 1, 1, 2, 2, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, { 'W','o','r','k','e','r' } }; //Worker
	unit[2] = { BASE_CHAR_INFO, 0, 2, 2, 2, 2, 2, 2, 1, 1, 2, 0, -2, 0, 0, 0, -2, { 'V','i','r','u','s' } }; //Basic Land unit

	unit[3] = { BASE_CHAR_INFO, 0, 4, 4, 3, 1, 1, 0, 4, 0, 0, 0, -3, 0, 0, 0, 1, { 'T','h','r','e','a','d' } }; //General resource building
	unit[3].charInfo.Char.UnicodeChar = 8801;
	unit[4] = { BASE_CHAR_INFO, 0, 4, 4, 4, 1, 1, 0, 4, 0, 0, 0, -1, 0, 0, 0, -1, { 'F','i','r','e','w','a','l','l' } }; // General upgrade building
	unit[4].charInfo.Char.UnicodeChar = 177;
	unit[7] = { BASE_CHAR_INFO, 0, 1, 1, 7, 100, 100, 1000, 1000, 100, 1, 0, -1000, 0, 0, 0, 0, { 'C','h','e','a','t','e','r','!'} }; //Unit for Land testing
	unit[7].charInfo.Char.UnicodeChar = 8734;
	unit[7].charInfo.Attributes = 0x0007;
	return 1;
}