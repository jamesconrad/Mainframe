#include "generationclass.h"
#include <stdio.h>
#include <stdlib.h>

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
}

int generationclass::generate()
{
	int generating[512][512];
	for (int x = 0; x <= generationclass::width; x++) {
		for (int y = 0; y <= generationclass::height; y++) {
			if (x > 2 && x < generationclass::width && y > 2 && y < generationclass::height) {
				for (int i = 0; i < 4; i++) {
					int rng = srand(generationclass::seed) % 3;
				}

			}
			
		}
	}
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