#ifndef GENERATIONCLASS_H
#define GENERATIONCLASS_H

#include <Windows.h>

class GenerationClass 
{
public:
	GenerationClass();
	GenerationClass(const GenerationClass&);
	~GenerationClass();
	int Initialize(int, int, int);

	int GetWidth();
	int GetHeight();

	int Save(char *, CHAR_INFO *);

	CHAR_INFO* Generate();

	void MainGen(int);
	void RoadGen(int, short);
	//void StructureGen(int);
	//void FeatureGen(int);

	bool NotAtBorder(int);
	bool IsWire(int);
	bool IsLand(int tile);

private:
	char *generated;
	int seed;
	int width, height;

	CHAR_INFO* map;
	//Terrain
	CHAR_INFO water, road, land, structure;

	double tile_ratio;
	double rng;
	int tile_start;

	double avg_r_len = 8;

	//Keeps track of how many of each tile are made
	int lT_count, rT_count,	tT_count, eT_count;

	int testcount = 0;		//variable i used for testing to see how many times certain things occurred
};

#endif