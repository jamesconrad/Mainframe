
#include "aiclass.h"

#define THREATSCALAR_NUMOFUNITS 1
#define THREATSCALAR_MISSINGHP 10
#define THREATSCALAR_AVGDMG 2
#define THREATSCALAR_AVGDEF 2
#define THREATSCALAR_AVGDISTANCE 2
#define THREATSCALAR_ECNOMOY 2
/*
AIClass::AIClass()
{

}

AIClass::AIClass(const AIClass&)
{

}

AICLass::~AIClass();
{

}
*/

int AIClass::Initialize(int playerNum, int attackRadius, int agression, int numOfPlayers, int mapWidth, const std::vector<EntityClass> *class_EntityArray)
{
	this->isAlive = true;
	this->playerNum = playerNum;
	this->attackRadius = attackRadius;
	this->currentPlayerTarget = (-1);
	this->agression = agression;
	this->numOfPlayers = numOfPlayers;
	this->mapWidth = mapWidth;
	this->threatValue = (int*)malloc(sizeof(int)*numOfPlayers);
	prevEntityArray.resize(class_EntityArray->size());
	prevEntityArray = *class_EntityArray;

	//find homebase coords
	for (int i = 0; i < class_EntityArray->size(); i++)
	{
		if (class_EntityArray->at(i).unitData.playerID == playerNum && class_EntityArray->at(i).unitData.unitID == 0)
		{
			homeBase.X = class_EntityArray->at(i).unitData.position % mapWidth;
			homeBase.Y = class_EntityArray->at(i).unitData.position / mapWidth;
		}
	}
	return 1;
}
int AIClass::MakeTurn(std::vector<EntityClass> *class_EntityArray)
{
	COORD unitPosition;

	this->CalculateAggression(class_EntityArray);
	this->CalculateTarget(class_EntityArray);




	//check if units fall within radius
	for (int myUnit = 0, n = class_EntityArray->size(); myUnit < n; myUnit++)
	{
		if (class_EntityArray->at(myUnit).unitData.playerID == playerNum)
		{
			for (int theirUnit = 0; theirUnit < class_EntityArray->size(); theirUnit++)
			{
				if (class_EntityArray->at(theirUnit).unitData.playerID == currentPlayerTarget)
				{
					unitPosition.Y = class_EntityArray->at(theirUnit).unitData.position / mapWidth;
					unitPosition.X = class_EntityArray->at(theirUnit).unitData.position % mapWidth;

					if (sqrt(pow(unitPosition.X - (class_EntityArray->at(myUnit).unitData.position % mapWidth), 2) + pow(unitPosition.Y - (class_EntityArray->at(myUnit).unitData.position / mapWidth), 2)) <= attackRadius)
					{
						//The unit is within attack radius
						//Next step is to consider action based off of aggression
						//Aggression is a number between 0 and 10 representing the percentage difference between
						//the target's threat and the ai's threat

					}
				}
			}
		}
	}






	prevEntityArray.resize(class_EntityArray->size());
	prevEntityArray = *class_EntityArray;

	return 1;
}

double AIClass::CalculateAggression(const std::vector<EntityClass> *class_EntityArray)
{
	if (currentPlayerTarget != -1)
	{
		aggression = threatValue[playerNum] / threatValue[currentPlayerTarget];
	}

	attackRadius = aggression * 10;

	return 1;
}

int AIClass::CalculateTarget(const std::vector<EntityClass> *class_EntityArray)
{
	int numOfUnits = 0,
		avgMissHP = 0,
		avgUnitDmg = 0,
		avgUnitDef = 0,
		avgThreat = 0,
		avgDistance = 0,
		economy = 0;

	COORD unitPosition;

	if (currentPlayerTarget == (-1))
		currentPlayerTarget = rand() % 6;

	for (int i = 0; i < numOfPlayers; i++)
	{
		for (int j = 0; j < class_EntityArray->size(); j++)
		{
			//If the unit we are looking at belongs to the player we are looking at
			if (class_EntityArray->at(j).unitData.playerID == i)
			{
				//get the missing hp for avg and numofunits
				numOfUnits++;
				avgMissHP += class_EntityArray->at(j).unitData.maxHP - class_EntityArray->at(j).unitData.hp;
				avgUnitDef += class_EntityArray->at(j).unitData.defense;
				avgUnitDmg += class_EntityArray->at(j).unitData.attack;

				//get each units distance from homebase
				unitPosition.Y = class_EntityArray->at(j).unitData.position / mapWidth;
				unitPosition.X = class_EntityArray->at(j).unitData.position % mapWidth;

				economy -= class_EntityArray->at(j).unitData.threadCost;

				avgDistance += sqrt(pow((unitPosition.X - homeBase.X), 2) * pow((unitPosition.Y - homeBase.Y), 2));
			}
		}
		//get avgMissingHP
		avgMissHP = avgMissHP / numOfUnits;
		//get avgUnitDef
		avgUnitDef = avgUnitDef / numOfUnits;
		//get avgUnitDmg
		avgUnitDmg = avgUnitDmg / numOfUnits;
		//get avgDistance
		avgDistance = avgDistance / numOfUnits;

		//set threat values
		threatValue[i] = numOfUnits * THREATSCALAR_NUMOFUNITS + 
			avgMissHP * THREATSCALAR_MISSINGHP + 
			avgDistance * THREATSCALAR_AVGDISTANCE + 
			avgUnitDef * THREATSCALAR_AVGDEF + 
			avgUnitDmg * THREATSCALAR_AVGDMG + 
			economy * THREATSCALAR_ECNOMOY;

		//reset values
		avgMissHP = avgUnitDef = avgUnitDmg = avgDistance = numOfUnits = 0;

		//add the player threat to average threat to calculate avgthreat
		avgThreat += threatValue[i];
	}

	//calculate avgthreat
	avgThreat = avgThreat / numOfPlayers;

	//if ai is under the average threat then we go into a defensive mode
	if (threatValue[playerNum] > avgThreat)
		currentPlayerTarget = 0;
	else
		currentPlayerTarget = -1;

	//find highest threat
	for (int i = 0; i < numOfPlayers; i++)
	{
		if (currentPlayerTarget != -1)
		{
			if (threatValue[currentPlayerTarget] > threatValue[i])
			{
				currentPlayerTarget = i;
			}
		}
	}

	return currentPlayerTarget;
}
