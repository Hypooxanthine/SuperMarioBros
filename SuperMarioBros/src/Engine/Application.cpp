#include "Application.h"

Application::Application()
	: window(nullptr), e(sf::Event())
{
	Log::init();
	window = MakeRef<sf::RenderWindow>(sf::VideoMode(256 * 4, 240 * 4, 32), "Super Marios Bros.", !sf::Style::Resize | !sf::Style::Fullscreen|sf::Style::Titlebar|sf::Style::Close);
	LOG_TRACE("Created Application.");

	states.push(MakeRef<GameState>(window));
}

Application::~Application()
{
	LOG_TRACE("Deleted Application.");
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
	if (!states.empty())
		states.top()->update(dt);
}

void Application::render()
{
	window->clear();

	//Render stuff here
	if (!states.empty())
		states.top()->render();

	window->display();
}

void Application::updateDt()
{
	dt = dtClock.restart().asSeconds();
}