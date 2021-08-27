#include "State.h"

State::State(Ref<sf::RenderWindow> window)
	: window(window), pendingKill(false)
{}

State::~State()
{
}
