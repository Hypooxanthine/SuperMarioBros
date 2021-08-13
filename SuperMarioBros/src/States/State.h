#pragma once

#include "../Core/Base.h"

class State
{
public:
	State(Ref<sf::RenderWindow> window);
	virtual ~State();

	virtual void update(const float& dt) = 0;
	virtual void render() = 0;

protected:
	Ref<sf::RenderWindow> window;
};

