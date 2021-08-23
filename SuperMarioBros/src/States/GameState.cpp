#include "GameState.h"

GameState::GameState(Ref<sf::RenderWindow> window)
	: State(window), level(MakeRef<Level>(window))
{

	if(!level->load("1-1"))
	{ 
		//TODO : handling loading error
	}

	LOG_TRACE("Constructed GameState.");
}

GameState::~GameState()
{
}

void GameState::update(const float& dt)
{

}

void GameState::render()
{
	if(level->isLoaded())
		level->render();
}

void GameState::init()
{
}

sf::Color GameState::getBackgroundColor() const
{
	if (level->isLoaded())
		return level->getBackgroundColor();
	else
		return sf::Color(0, 0, 0);
}
