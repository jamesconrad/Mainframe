#include <iostream>
#include <Windows.h>
#include <ctime>

#include "worldclass.h"
#include "clientclass.h"
#include "serverclass.h"
#include "generationclass.h"
void cls(HANDLE);

int main() {

	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	cls(hStdout);

	time_t now = time(&now);
	time_t lastRender;
	bool running = true;
	generationclass TerrainGenerator;
	worldclass World;
	TerrainGenerator.initialize(512, 512, 50982);
	World.initialize(TerrainGenerator.generate(), 32, 32);
	World.render(2, 2);
	time(&lastRender);
	//cls(hStdout);
	//screen should be re rendered every half second or every time keyboard input is detected
	//TerrainGenerator.generate();
	TerrainGenerator.save("savedata.txt", World.getMap());
	int worldFrameX = World.getFrameX();
	int worldFrameY = World.getFrameY();
	while (running) {
		//temp game loop
		
		if (GetAsyncKeyState(VK_UP)){
			worldFrameY++;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_DOWN)){
			worldFrameY--;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_LEFT)){
			worldFrameX--;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_RIGHT)){
			worldFrameX++;
			Sleep(100);
		}

		World.changeFrame(worldFrameX, worldFrameY);

		time(&now);
		if (difftime(now, lastRender) >= 0.5){
			cls(hStdout);
			World.render(2,2);
			time(&lastRender);
		}


		if (GetAsyncKeyState(VK_ESCAPE))
			running = false;
	}
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