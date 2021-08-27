#pragma once

#include "../Core/Base.h"

class State
{
public:
	State(Ref<sf::RenderWindow> window);
	virtual ~State();

	virtual void updateEvents(sf::Event& e, const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render() = 0;
	virtual void init() = 0;
	virtual sf::Color getBackgroundColor() const = 0;

	inline const bool& isPendingKill() const { return pendingKill; }
	virtual Ref<State> getNextState() const = 0;

protected:
	inline void endState() { pendingKill = true; }

	Ref<sf::RenderWindow> window;
	
	bool pendingKill;
};

