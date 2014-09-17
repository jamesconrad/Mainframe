#include <iostream>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include "worldclass.h"
#include "clientclass.h"
#include "serverclass.h"
#include "generationclass.h"

int main() {
	generationclass TerrainGenerator;
	TerrainGenerator.initialize(32, 32, 32);
	//TerrainGenerator.generate();
	TerrainGenerator.save("savedata.txt", TerrainGenerator.generate());
}