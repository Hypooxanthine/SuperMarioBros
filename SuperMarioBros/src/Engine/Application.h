#pragma once

#include "../Core/Base.h"

class Application
{
public:
	Application();

	virtual ~Application();

	void run();
	void manageEvents();
	void update();
	void render();
	void updateDt();

private:
	// Windowing
	Ref<sf::RenderWindow> window;
	sf::Event e;

	// Time managing
	float dt = 0.f;
	sf::Clock dtClock;
};

