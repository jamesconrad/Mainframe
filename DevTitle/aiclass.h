#ifndef AICLASS_H
#define AICLASS_H

#include <Windows.h>
#include <vector>
#include "entityclass.h"

class AIClass
{
public:
	/*
	AIClass();
	AIClass(const AIClass&);
	~AIClass();
	*/

	int MakeTurn(std::vector<EntityClass> *class_EntityArray);
	int Initialize(int playerNum, int attackRadius, int agression, int numOfPlayers, int mapWidth, const std::vector<EntityClass> *class_EntityArray);

private:
	bool isAlive;
	COORD homeBase;
	double aggression;
	int playerNum,
		attackRadius,
		currentPlayerTarget,
		agression,
		numOfPlayers,
		mapWidth,
		*threatValue;

	std::vector<EntityClass> prevEntityArray;

	double CalculateAggression(const std::vector<EntityClass> *class_EntityArray);
	int CalculateTarget(const std::vector<EntityClass> *class_EntityArray);

};

#endif