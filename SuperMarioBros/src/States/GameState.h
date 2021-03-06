#pragma once

#include "State.h"
#include "../Level/Level.h"

class GameState : public State
{
public:
	GameState(Ref<sf::RenderWindow> window);
	virtual ~GameState();

	virtual void updateEvents(sf::Event& e, const float& dt) override;
	virtual void update(const float& dt) override;
	virtual void render() override;
	virtual void init() override;

	virtual Ref<State> getNextState() const override;

	virtual sf::Color getBackgroundColor() const override;

private:
	Ref<Level> level;
};

