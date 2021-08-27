#include "GameState.h"

GameState::GameState(Ref<sf::RenderWindow> window)
	: State(window), level(MakeRef<Level>(window))
{
	LOG_TRACE("Constructed GameState.");
}

GameState::~GameState()
{
}

void GameState::init()
{

}

void GameState::updateEvents(sf::Event& e, const float& dt)
{
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
		endState();
}

void GameState::update(const float& dt)
{

}

void GameState::render()
{

}

Ref<State> GameState::getNextState() const
{
	return nullptr;
}

sf::Color GameState::getBackgroundColor() const
{
	if (level->isLoaded())
		return level->getBackgroundColor();
	else
		return sf::Color(0, 0, 0);
}
