#include <Windows.h>

using namespace std;

class GenerationClass {
private:
	char * generated;
	int seed;
	int width, height;

public:
	GenerationClass();
	GenerationClass(const GenerationClass&);
	~GenerationClass();

	int Initialize(int, int, int);
	CHAR_INFO * * Generate();
	int Save(char *, CHAR_INFO * *);
};

//This is the class that creates the save file, and terrain.
//ASCII values of char's are used to learn what state the tile is in
//Ex 1-10 = terrain, 11 represents unit1 on terrain 1 on team 1, 16 represents unit6 on terrain 1 on team 1
//255 represents spawn base of team 6
//Buildings will negate all values of terrain and become its own version of terrain.