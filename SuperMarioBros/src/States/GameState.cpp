#include "GameState.h"

GameState::GameState(Ref<sf::RenderWindow> window)
	: State(window), level(MakeRef<Level>(window))
{
	LOG_TRACE("Constructed GameState.");

	if (!load("1-1"))
	{
		//TODO : handle level loading error.
	}
}

GameState::~GameState()
{
}

void GameState::update(const float& dt)
{
}

void GameState::render()
{
	level->render();
}
