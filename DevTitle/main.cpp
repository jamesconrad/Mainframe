#include <iostream>
#include <Windows.h>
#include "worldclass.h"
#include "clientclass.h"
#include "serverclass.h"
#include "generationclass.h"
void cls(HANDLE);

int main() {

	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	cls(hStdout);

	generationclass TerrainGenerator;
	worldclass World;
	TerrainGenerator.initialize(128, 128, 50982);
	World.initialize(TerrainGenerator.generate(), 8, 8);
	World.render(8, 8);
	//cls(hStdout);
	//screen should be re rendered every half second or every time keyboard input is detected
	//TerrainGenerator.generate();
	TerrainGenerator.save("savedata.txt", World.getMap());

}

//The function cls(HANDLE) was taken from www.cplusplus.com/forum/beginner/1988/3/#msg10830 to solve the security issue of using a system(char*) call.
//"Grey Wolf" (2008, July, 8) "Console Closing Down - C++ Forum" Retrieved from www.cplusplus.com/forum/beginner/1988/3/#msg10830
void cls(HANDLE hConsole){
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten))
		return;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
		return;

	SetConsoleCursorPosition(hConsole, coordScreen);
}