#ifndef CONBUFFERCLASS_H
#define CONBUFFERCLASS_H

#include <Windows.h>

class ConBufferClass 
{
public:
	HANDLE hConsole;

	ConBufferClass();
	ConBufferClass(const ConBufferClass&);
	~ConBufferClass();
	int Initialize();

	int OutputScreen(CHAR_INFO*, CHAR_INFO*, int, int, COORD, COORD);
	int ClearConsole(HANDLE, COORD);
private:
	COORD beginCoords; 
	DWORD nWritten;

	time_t now;
	time_t lastRender;

	CHAR_INFO *border;

	int RenderBorder();
	int InitiazlizeBorder();

	bool unitsRendered;
};

#endif