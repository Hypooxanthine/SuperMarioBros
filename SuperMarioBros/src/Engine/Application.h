#pragma once

#include "../Core/Base.h"

#include "../States/States.h"
#include <stack>

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
	void checkState();

private:
	// Windowing
	Ref<sf::RenderWindow> window;
	sf::Event e;

	// Time managing
	float dt = 0.f;
	sf::Clock dtClock;

	// States
	std::stack<Ref<State>> states;
};

