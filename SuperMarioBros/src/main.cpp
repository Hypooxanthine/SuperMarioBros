#include "Engine/Application.h"

int main()
{
	Application* app = new Application();

	app->run();

	delete app;

	std::cin.get();

	return 0;
}