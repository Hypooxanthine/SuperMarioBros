#include "MainState.h"

#include "GameState.h"
#include "EditorState.h"

MainState::MainState(Ref<sf::RenderWindow> window)
	: State(window), choice(Choice::Game)
{
}

MainState::~MainState()
{
}

void MainState::init()
{
	std::cout << "What to do ?\n";
	std::cout << "   1. Game\n";
	std::cout << "   2. Editor\n";
	std::cout << "   3. Exit\n";
	choice = (Choice)(getUserIntRange("Choice", 1, 3) - 1);
	endState();
}

void MainState::updateEvents(sf::Event& e, const float& dt)
{
}

void MainState::update(const float& dt)
{
}

void MainState::render()
{
}

sf::Color MainState::getBackgroundColor() const
{
	return sf::Color::Black;
}

Ref<State> MainState::getNextState() const
{
	switch (choice)
	{
	case Choice::Game:
		return MakeRef<GameState>(window);
		break;
	case Choice::Editor:
		return MakeRef<EditorState>(window);
		break;
	case Choice::Quit:
	default:
		return nullptr;
		break;
	}
}
