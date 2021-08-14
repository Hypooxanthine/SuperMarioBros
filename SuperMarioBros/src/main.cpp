#include "Engine/Application.h"

int main()
{
	#ifndef _DEBUG
		HWND hWnd = GetConsoleWindow();
		ShowWindow(hWnd, SW_HIDE);
	#endif

	Log::init();
	
	#if 1
	Application* app = new Application();

	app->run();

	delete app;
	#endif

	#ifdef _DEBUG
	std::cin.get();
	#endif

	return 0;
}