#include <vector>

using namespace std;

class worldclass {
private:
	int framex, framey;
	vector<vector<char>> worldmap;

public:
	worldclass();
	worldclass(const worldclass&);
	~worldclass();

	vector<vector<char>> getMap();
	int initialize(vector<vector<char>>, int, int);
	int changeFrame(int, int);
	int updateTile(int, int, int);
	int render(int, int);
};