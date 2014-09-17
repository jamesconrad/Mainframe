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
	worldclass World;
	TerrainGenerator.initialize(32, 32, 32);
	World.initialize(TerrainGenerator.generate(), 16, 16);
	World.render(16, 16);
	//TerrainGenerator.generate();
	TerrainGenerator.save("savedata.txt", World.getMap());

}