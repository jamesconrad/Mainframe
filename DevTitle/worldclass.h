#include "conbufferclass.h"
#include <Windows.h>

class WorldClass {
private:
	int frame;
	CHAR_INFO* worldMap;
	bool cursorRenderd = false;
	int height, width;

	ConBufferClass class_ConBuffer;
	CHAR_INFO cursor;
public:
	WorldClass();
	WorldClass(const WorldClass&);
	~WorldClass();

	CHAR_INFO* GetMap();
	COORD ConvertIndex(int);
	int ConvertCoord(COORD);
	int Initialize(CHAR_INFO* , int, int, int);
	int ChangeFrame(int);
	int UpdateTile(int, int, int);
	int Render();
	int GetFrame();
};