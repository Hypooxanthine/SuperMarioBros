#include "Application.h"

Application::Application()
	: window(nullptr), e(sf::Event())
{
	window = MakeRef<sf::RenderWindow>(sf::VideoMode(256 * 4, 240 * 4, 32), "Super Marios Bros.", !sf::Style::Resize | !sf::Style::Fullscreen|sf::Style::Titlebar|sf::Style::Close);
	LOG_TRACE("Created Application.");
}

Application::~Application()
{
	LOG_TRACE("Deleted Application.");
}

void Application::run()
{
	states.push(MakeRef<EditorState>(window));
	states.top()->init();

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

		if (!states.empty())
			states.top()->updateEvents(e, dt);
	}
}

void Application::update()
{
	if (!states.empty())
		states.top()->update(dt);

	//LOG_INFO("FPS : {}", 1.f / dt);
}

void Application::render()
{
	window->clear(states.empty() ? sf::Color::Black : states.top()->getBackgroundColor());

	//Render stuff here
	if (!states.empty())
		states.top()->render();

	window->display();
}

void Application::updateDt()
{
	dt = dtClock.restart().asSeconds();
}