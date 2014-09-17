#include "generationclass.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

generationclass::generationclass()
{
}

generationclass::generationclass(const generationclass& other)
{
}

generationclass::~generationclass()
{
}

int generationclass::initialize(int width, int height, int seed) {
	generationclass::width = width;
	generationclass::height = height;
	generationclass::seed = seed;
	return 1;
}


vector<vector<char>> generationclass::generate()
{
	vector<vector<char>> generating;
	generating.resize(generationclass::height);
	for (int i = 0; i < generationclass::height; i++)
		generating[i].resize(generationclass::width);
	char rng;
	char prevrng = '1';
	int progress = 0;
	srand(generationclass::seed);
	for (int y = 0; y < generationclass::height; y++) {
		for (int x = 0; x < generationclass::width; x++) {
			rng = rand() % 10;
			if (rand()%100 >= 80) {
				generating[x][y] = prevrng;
				prevrng = rng;
				progress++;
			}
			else {
				generating[x][y] = rng;
				progress++;
			}
		}
	}
	cout << "Generation Complete." << endl;
	return generating;
}

int generationclass::save(char * filePath, vector<vector<char>> saveData)
{
	ofstream savefile;
	savefile.open(filePath);
	for (int y = 0; y < generationclass::height; y++) {
		for (int x = 0; x < generationclass::width; x++) {
			savefile << saveData[x][y];
		}
		savefile << endl;
	}
	savefile.close();
	return 1;
}

/*
Possible terrain generation
0 - water
1 - plains
2 - hills
3 - forrest
4 - forrested hills
5 - mountain
*/