#include <vector>
using namespace std;

class generationclass {
private:
	char * generated;
	int seed;
	int width, height;

public:
	generationclass();
	generationclass(const generationclass&);
	~generationclass();

	int initialize(int, int, int);
	vector<vector<char>> generate();
	int save(char *, vector<vector<char>>);
};

//This is the class that creates the save file, and terrain.
//ASCII values of char's are used to learn what state the tile is in
//Ex 1-10 = terrain, 11 represents unit1 on terrain 1 on team 1, 16 represents unit6 on terrain 1 on team 1
//255 represents spawn base of team 6
//Buildings will negate all values of terrain and become its own version of terrain.