#include "Core/Application.h"

#include <fstream>

void fillMap()
{
	std::ofstream file;
	file.open("Resources/levels.txt");

	if (file.is_open())
	{
		file << "1-1\n" << "224 30\n";
		for (size_t y = 0; y < 30; y++)
		{
			for (size_t x = 0; x < 224; x++)
			{
				if (y < 28)
					file << " 0";
				else
					file << " 1";
			}

			file << "\n";

		}
	}
}

int main()
{
	//fillMap();

	Log::init();

	Application* app = new Application();

	app->run();

	delete app;

	std::cin.get();
	std::cin.get();

	return 0;
}