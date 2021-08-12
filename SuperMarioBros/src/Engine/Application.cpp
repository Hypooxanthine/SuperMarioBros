#include "Application.h"

Application::Application()
	: window(MakeRef<sf::RenderWindow>(sf::VideoMode(500, 500, 32), "Super Marios Bros."))
{
}

void Application::run()
{
	while (window->isOpen())
	{
		manageEvents();
		update();
		render();
		updateDt();
	}
}

void Application::manageEvents()
{
	while (window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			window->close();
	}
}

void Application::update()
{

}

void Application::render()
{
	window->clear();

	//Render stuff here


	window->display();
}

void Application::updateDt()
{
	dt = dtClock.restart().asSeconds();
}