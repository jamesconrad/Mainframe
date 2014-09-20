#include "conbufferclass.h"
#include <Windows.h>

class WorldClass {
private:
	int framex, framey;
	CHAR_INFO* worldMap;
	bool cursorRenderd = false;

	ConBufferClass class_ConBuffer;

public:
	WorldClass();
	WorldClass(const WorldClass&);
	~WorldClass();

	CHAR_INFO* GetMap();
	int Initialize(CHAR_INFO* , int, int);
	int ChangeFrame(int, int);
	int UpdateTile(int, int, int);
	int Render(int, int);
	int GetFrameX();
	int GetFrameY();
};