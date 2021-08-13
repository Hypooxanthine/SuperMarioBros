#pragma once

#include "State.h"

class GameState : public State
{
public:
	GameState(Ref<sf::RenderWindow> window);
	virtual ~GameState();

	virtual void update(const float& dt) override;
	virtual void render() override;

private:
};

