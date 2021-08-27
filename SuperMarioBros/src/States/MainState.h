#pragma once

#include "State.h"

class MainState : public State
{
public:
	MainState(Ref<sf::RenderWindow> window);
	virtual ~MainState();

	virtual void init() override;
	virtual void updateEvents(sf::Event& e, const float& dt) override;
	virtual void update(const float& dt) override;
	virtual void render() override;

	virtual sf::Color getBackgroundColor() const override;

	virtual Ref<State> getNextState() const override;

private:
	enum class Choice { Game, Editor, Quit };

	Choice choice;
};

