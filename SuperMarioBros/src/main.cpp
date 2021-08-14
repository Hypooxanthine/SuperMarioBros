#include "Engine/Application.h"

int main()
{
	#ifndef _DEBUG
		HWND hWnd = GetConsoleWindow();
		ShowWindow(hWnd, SW_HIDE);
	#endif

	Log::init();
	
	Application* app = new Application();

	app->run();

	delete app;

	return 0;
}